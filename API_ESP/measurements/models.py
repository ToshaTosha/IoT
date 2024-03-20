from sqlalchemy import Column, Float, String, DateTime, Integer
import database
from datetime import datetime

class Temperature(database.Base):
    __tablename__ = "temperature"
    id = Column(Integer, primary_key=True, index=True)
    value = Column(Float)
    location = Column(String)
    device_id = Column(String)
    timestamp = Column(DateTime, default=datetime.now)
