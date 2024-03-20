from measurements.models import Temperature
from measurements.schemas import AddTemperatureRequest
from sqlalchemy.orm import Session


def create_temperature_value(request: AddTemperatureRequest, db: Session):
    temperature_data = Temperature(value=request.value, location=request.location, device_id=request.device_id)

    try:
        db.add(temperature_data)
        db.commit()
        db.refresh(temperature_data)
    except Exception as e:
        print(e)
    return {"message": "Temperature has been stored successfully"}


def get_temperature__by_location(location: str, db: Session):
    try:
        request = db.query(Temperature).filter(Temperature.location == location).all()
    except Exception as e:
        print(e)
    return request
    
