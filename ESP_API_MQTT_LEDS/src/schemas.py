from pydantic import BaseModel

class User(BaseModel):
    login: str
    password: str

class Device(BaseModel):
    id: int
    id_user: int
    name: str

class Color(BaseModel):
    id_user: int
    hex_code: str

class DeviceColor(BaseModel):
    device_id: int
    color_id: int