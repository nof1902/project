FROM python:3.6-slim-buster

WORKDIR /flask-crud-rest

COPY requirements.txt ./

RUN pip install -r requirements.txt

COPY . .

EXPOSE 8080

CMD [ "flask", "run", "--host=0.0.0.0", "--port=8080"]
