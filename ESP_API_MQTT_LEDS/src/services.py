from src.models import User
from src.schemas import User, Device, Color
from sqlalchemy.orm import Session


def registration_handler(request_data, db, model):
   data = model(**request_data.dict())
   try:
       db.add(data)
       db.commit()
       db.refresh(data)
       return {"message": f"{model.__name__} has been registered successfully"}
   except Exception as e:
       print(e)