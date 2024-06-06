import dash
from dash import dcc, html
import plotly.express as px
import pandas as pd
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy import Column, Integer, Float, DateTime
from datetime import datetime

# Подключение к базе данных
SQLALCHEMY_DATABASE_URL = "sqlite:///./test.db"
engine = create_engine(SQLALCHEMY_DATABASE_URL, connect_args={"check_same_thread": False})
Session = sessionmaker(bind=engine)
session = Session()

# Определение модели
Base = declarative_base()
class Item(Base):
    __tablename__ = "items"
    id = Column(Integer, primary_key=True, index=True)
    pm10 = Column(Integer, index=True)
    pm25 = Column(Integer, index=True)
    temperature = Column(Float, index=True)
    pressure = Column(Float, index=True)
    altitude = Column(Float, index=True)
    humidity = Column(Float, index=True)
    timestamp = Column(DateTime, default=datetime.utcnow)

# Создание экземпляра Dash
app = dash.Dash(__name__)

# Функция для обновления данных
def update_data():
    query = session.query(Item.timestamp, Item.temperature, Item.pressure).all()
    df = pd.DataFrame(query, columns=['timestamp', 'temperature', 'pressure'])
    return df

# Создание графиков с использованием Dash
app.layout = html.Div([
    dcc.Interval(
        id='interval-component',
        interval=10*1000,  # в миллисекундах
        n_intervals=0
    ),
    dcc.Graph(id='temperature-graph'),
    dcc.Graph(id='pressure-graph')
])

# Обновление данных и графиков
@app.callback(
    [dash.dependencies.Output('temperature-graph', 'figure'),
     dash.dependencies.Output('pressure-graph', 'figure')],
    [dash.dependencies.Input('interval-component', 'n_intervals')]
)
def update_graphs(n):
    df = update_data()
    temperature_fig = px.line(df, x='timestamp', y='temperature', title='Temperature')
    pressure_fig = px.line(df, x='timestamp', y='pressure', title='Pressure')
    return temperature_fig, pressure_fig

if __name__ == '__main__':
    app.run_server(debug=True)