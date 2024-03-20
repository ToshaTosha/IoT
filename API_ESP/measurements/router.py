from fastapi import APIRouter, Depends
from sqlalchemy.orm import Session
from database import SessionLocal
from . import schemas, models

router = APIRouter()

@router.post("/temperature")
def create_temperature_value(temp_value: schemas.TemperatureValue, db: Session = Depends(SessionLocal)):
    temperature_data = models.Temperature(value=temp_value.value, location=temp_value.location, device_id=temp_value.device_id)
    db.add(temperature_data)
    db.commit()
    return {"message": "Temperature has been stored successfully"}

@router.get("/temperature/{location}")
def get_temperature_values(location: str, db: Session = Depends(SessionLocal)):
    temperatures = db.query(models.Temperature).filter(models.Temperature.location == location).all()
    return temperatures
