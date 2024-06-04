from fastapi import FastAPI
from pydantic import BaseModel
from sqlalchemy import create_engine, Column, Integer, String, Float, DateTime
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker
import uvicorn
from datetime import datetime

# Создаем экземпляр FastAPI
app = FastAPI()

# Подключение к базе данных
SQLALCHEMY_DATABASE_URL = "sqlite:///./test.db"
engine = create_engine(SQLALCHEMY_DATABASE_URL, connect_args={"check_same_thread": False})
SessionLocal = sessionmaker(autocommit=False, autoflush=False, bind=engine)

Base = declarative_base()

# Модель данных для хранения объекта
class Item(Base):
    __tablename__ = "items"
    id = Column(Integer, primary_key=True, index=True)
    pm10 = Column(Integer, index=True)
    pm25 = Column(Integer, index=True)
    temperature = Column(Float, index=True)
    pressure = Column(Float, index=True)
    altitude = Column(Float, index=True)
    humidity = Column(Float, index=True)
    timestamp = Column(DateTime, default=datetime.now)

# Создание таблицы в базе данных
Base.metadata.create_all(bind=engine)

# Передаваемый объект
class ItemIn(BaseModel):
    pm10: int
    pm25: int
    temperature: float
    pressure: float
    altitude: float
    humidity: float
    timestamp: datetime


# Маршрут для сохранения объекта в базу данных
@app.post("/items")
async def create_item(item: ItemIn):
    db = SessionLocal()
    db_item = Item(
        pm10=item.pm10,
        pm25=item.pm25,
        temperature=item.temperature,
        pressure=item.pressure,
        altitude=item.altitude,
        humidity=item.humidity)
    db.add(db_item)
    db.commit()
    db.refresh(db_item)
    return db_item

if __name__ == "__main__":
    uvicorn.run(app, host="0.0.0.0", port=8005)
