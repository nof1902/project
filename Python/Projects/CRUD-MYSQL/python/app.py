import mysql.connector
from flask import Flask, request, json, jsonify, current_app, make_response

mydb = mysql.connector.connect(
    host='localhost',
    user='nofar',
    password='1234',
    database='Patients',
)
app = Flask(__name__)
app.json.sort_keys = False

@app.route('/Patients', methods=['GET'])
def get_all_patients():
    # Use the database connection to fetch the employees
    my_cursor = mydb.cursor()
    my_cursor.execute('SELECT * FROM Patients')
    my_patients = my_cursor.fetchall()

    patients = list()
    for Patients in my_patients:
        patients.append(
            {
                'Id': Patients[0],
                'First_Name': Patients[1],
                'Last_Name': Patients[2],
                'Date_Of_Birth': Patients[3],
                'Last_Visit': Patients[4],
            }
        )

    return make_response(
        jsonify(
            message='Patients List',
            data=patients
        )
    )


@app.route('/Patients/<Id>', methods=['GET'])
def get_specific_patient(Id):

    my_cursor = mydb.cursor()
    sql = f"SELECT * FROM Patients WHERE Id = %s"
    val = (Id,)
    my_cursor.execute(sql, val)
    my_patients = my_cursor.fetchall()

    patients = list()
    for Patients in my_patients:
        patients.append(
            {
                'Id': Patients[0],
                'First_Name': Patients[1],
                'Last_Name': Patients[2],
                'Date_Of_Birth': Patients[3],
                'Last_Visit': Patients[4],
            }
        )
    return make_response(
        jsonify(
            message='Patients List',
            data=patients
        )
    )

@app.route('/Patients/<id>', methods=['DELETE'])
def remove_patient(Id):
    # Use the database connection to delete the employee
    my_cursor = mydb.cursor()

    sql = f"DELETE FROM Patients WHERE id = %s"
    val = (Id,)
    my_cursor.execute(sql, val)
    mydb.commit()

    return make_response(
        jsonify(
            message='Employee Successfully removed',
            Id=Id)
    )

@app.route('/Patients/<id>', methods=['POST'])
def create_patient(Id):
    patients = request.json
    my_cursor = mydb.cursor()
    sql = f"INSERT INTO Patients()WHERE id = %s"
    val = (Id,)


    sql = f"INSERT INTO Patients (Id, First_Name, Last_Name, Date_Of_Birth," \
        f"Last_Visit) VALUES ('{patients['Id']}', " \
        f"'{patients['First_Name']}', '{patients['Last_Name']}'," \
        f"' {patients['Date_Of_Birth']}, {patients['Last_Visit']})"
    
    my_cursor.execute(sql)
    mydb.commit()

    return make_response(
        jsonify(
            message='Patients Successfully added',
            data=patients)
    )


if __name__ == '__main__':
    app.run(debug=True)
