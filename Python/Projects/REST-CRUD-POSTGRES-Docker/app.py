#request - make the http request, 
#jsonify - work with data data in json format
#make_response - package to handle responses in python

from flask import Flask, request, jsonify, make_response
from flask_sqlalchemy import SQLAlchemy #ORM format
from os import environ

#Create instanse of the flask app
app = Flask(__name__)

#Create the conection with the database
app.config['SQLALCHEMY_DATABASE_URI'] = environ.get('DB_URL')
#app.config['SQLALCHEMY_DATABASE_URI'] = postgresql://postgres:postgres@localhost:5432/postgres
db = SQLAlchemy(app)

#create the database & the table
class Patient(db.Model):
    __tablename__ = 'patients'

    id = db.Column(db.Integer, primary_key=True)
    first_name = db.Column(db.String(20), unique=True, nullable=False)
    last_name = db.Column(db.String(30), unique=True, nullable=False)
    date_of_birth = db.Column(db.String(10), nullable=False)
    phone = db.Column(db.String(10), nullable=False)

    def json(self):
        return {
           'id': self.id,
           'first_name': self.first_name, 
            'last_name': self.last_name,
            'date_of_birth': self.date_of_birth,
            'phone': self.phone
            }

#initialize database
db.create_all()

@app.route('/patients', methods=['GET'])
def get_patients():
  try:
    patients = Patient.query.all()
    return make_response(jsonify([Patient.json() for Patient in patients]), 200)
  except Exception as e:
    print("Error in get_patients:", str(e))
    return make_response(jsonify({'message': 'error getting users'}), 500)
      

@app.route('/patients/<int:id>', methods=['GET'])
def get_patient(id):
    try:
        patient = Patient.query.filter_by(id=id).first()
        if patient:
           return make_response(jsonify({'Patient': patient.json()}), 200)
        else:
           return make_response(jsonify({'message': 'Patient not found'}), 404)
    except Exception as e:
        return make_response(jsonify({'message': 'error getting Patient'}), 500)


@app.route('/patients', methods=['POST'])
def create_patient():
    try:
        data = request.get_json()
        new_patient = Patient(id=data['id'],
                              first_name=data['first_name'],
                              last_name=data['last_name'],
                              date_of_birth=data['date_of_birth'],
                              phone=data['phone'])
        
        db.session.add(new_patient)
        db.session.commit()
        return make_response(jsonify({'Patient': 'patient created'}), 201)
    except Exception as e:
      print("Error in get_patients:", str(e))
      return make_response(jsonify({'Patient': 'error creating patient'}), 500)

@app.route('/patients/<int:id>', methods=['PUT'])
def update_patient(id):
    try:
        patient = Patient.query.filter_by(id=id).first()
        if patient:
            data = request.get_json()
            patient.id = data['id']
            patient.first_name = data['first_name']
            patient.last_name = data['last_name']
            patient.date_of_birth = data['date_of_birth']
            patient.phone = data['phone']
            db.session.commit()
            return make_response(jsonify({'Patient': 'patient updated'}), 201)
        else:
            return make_response(jsonify({'message': 'patient not found'}), 404)
    except Exception as e:
      return make_response(jsonify({'Patient': 'error updating patient'}), 500)

@app.route('/patients/<int:id>', methods=['DELETE'])
def delete_patient(id):
    try:
        patient = Patient.query.filter_by(id=id).first()
        if patient:
            db.session.delete(patient)
            db.session.commit()
            return make_response(jsonify
                                ({'Patient': 'patient deleted'}), 200)
        else:
            return make_response(jsonify
                                ({'message': 'patient not found'}), 404) 
    except Exception as e:
        return make_response(jsonify
                                ({'Patient': 'error deleting patient'}), 500)
#Run Server
if __name__ == '__main__':
   app.run(debug=True)
    