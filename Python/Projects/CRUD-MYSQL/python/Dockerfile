# NOTE name need to be Dockerfile
FROM python:3.10.6

RUN pip install -r requirements.txt

WORKDIR /usr/app/src

COPY app.py ./

EXPOSE 8080

CMD [ "flask", "run", "--host=0.0.0.0", "--port=8080"]