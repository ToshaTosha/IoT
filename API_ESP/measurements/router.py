from sqlalchemy.orm import Session
from fastapi import APIRouter, Depends
from database import get_db
from measurements.schemas import AddTemperatureRequest
import measurements.services as services

router = APIRouter()

@router.post("/temperature", tags=["temperature"])
async def create_temperature(request: AddTemperatureRequest, db: Session=Depends(get_db)):
    return services.create_temperature_value(request, db)


@router.get("/temperature", tags=["temperature"])
async def create_temperature(location: str, db: Session=Depends(get_db)):
    return services.get_temperature__by_location(location, db)

