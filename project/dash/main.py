import dash
from dash import dcc, html
import plotly.express as px
import pandas as pd
import requests

df = pd.DataFrame(requests.get('http://server:8000/data').json())

# Создание экземпляра Dash
app_dash = dash.Dash(__name__)

# Определение макета для приложения Dash
app_dash.layout = html.Div([
    dcc.Graph(id='graph'),
])

# Обновление графика при изменении данных
@app_dash.callback(
    dash.dependencies.Output('graph', 'figure'),
    [dash.dependencies.Input('dropdown', 'value')]
)
def update_graph(selected_value):
    fig = px.scatter(df, x='name', y='description', title='График')
    return fig


if __name__ == '__main__':
    app_dash.run_server(debug=True)