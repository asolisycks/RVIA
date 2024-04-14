import pandas as pd
import psycopg2 as pg
import glob
import gspread
from oauth2client.service_account import ServiceAccountCredentials



# Usa tus propias credenciales de la API de Google Sheets
scope = ['https://spreadsheets.google.com/feeds',
         'https://www.googleapis.com/auth/drive']
creds = ServiceAccountCredentials.from_json_keyfile_name('client_secret.json', scope)
client = gspread.authorize(creds)

# Crea una nueva hoja de cálculo de Google
spreadsheet = client.create('Unión de archivos CSV')

# Encuentra todos los archivos .csv en el directorio actual
csv_files = glob.glob('*.csv')

for file in csv_files:
    # Lee el archivo .csv en un DataFrame de pandas
    df = pd.read_csv(file)
    
    # Convierte el DataFrame a una lista de listas
    data = df.values.tolist()
    
    # Añade los nombres de las columnas al principio de la lista
    data.insert(0, df.columns.tolist())
    
    # Añade una nueva hoja al archivo de Google Sheets con el nombre del archivo .csv
    worksheet = spreadsheet.add_worksheet(title=file, rows="100", cols="20")
    
    # Escribe los datos en la hoja de cálculo
    worksheet.insert_rows(data, row=1)

