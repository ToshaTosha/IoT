FROM python:3.10

WORKDIR /app

RUN pip install poetry

COPY poetry.lock pyproject.toml ./

RUN poetry install

COPY . .

EXPOSE 8000

CMD ["poetry", "run", "python", "main.py"]