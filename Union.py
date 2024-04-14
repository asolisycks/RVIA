import pandas as pd
import psycopg2 as pg

try:
    p1 = 'p1.csv'
    datos_p1 = pd.read_csv(p1)

    p2 = 'p2.csv'
    datos_p2 = pd.read_csv(p2)

    p3 = 'p3.csv'
    datos_p3 = pd.read_csv(p3)

    p4 = 'p4.csv'
    datos_p4 = pd.read_csv(p4)

    # Crear un nuevo DataFrame con cuatro hojas
    datos_combinados = {
        'Hoja1': datos_p1,
        'Hoja2': datos_p2,
        'Hoja3': datos_p3,
        'Hoja4': datos_p4
    }

    # Guardar cada hoja en un solo archivo CSV con diferentes hojas
    with pd.ExcelWriter('archivo_combinado.xlsx', engine='xlsxwriter') as writer:
        for hoja_nombre, hoja_datos in datos_combinados.items():
            hoja_datos.to_excel(writer, sheet_name=hoja_nombre, index=False)

    print(f'LISTO')

except Exception as e:
    print(f'ERROR {e}')