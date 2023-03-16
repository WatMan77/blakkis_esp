FROM python:3.10.0-bullseye

RUN python3 -m pip install python-telegram 

RUN pip install flask python-dotenv

COPY server.py .

COPY .env .

EXPOSE 5000

ENV FLASK_APP server.py

CMD ["flask", "run", "--host=0.0.0.0"]