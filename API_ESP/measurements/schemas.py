from datetime import datetime
from pydantic import BaseModel

class TemperatureValue(BaseModel):
    value: float 
    location: str
    device_id: str
    timestamp: datetime

class AddTemperatureRequest(BaseModel):
    value: float
    location: str | None
    device_id: str
