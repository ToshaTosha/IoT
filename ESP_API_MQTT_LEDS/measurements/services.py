from measurements.models import User
from measurements.schemas import User
from sqlalchemy.orm import Session

def user_registration(request: User, db: Session):
    temperature_data = User(login=request.login, password=request.password)

    try:
        db.add(temperature_data)
        db.commit()
        db.refresh(temperature_data)
    except Exception as e:
        print(e)
    return {"message": "Temperature has been stored successfully"}
