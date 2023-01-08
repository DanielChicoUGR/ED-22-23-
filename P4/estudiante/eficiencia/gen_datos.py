import envoy as envoy

import csv

# from csv import dia

MIN_LETRAS = 3
MAX_LETRAS = 20

ARCHIVOS_EJECUCION = envoy.run("ls data_eficiencia").std_out.split('\n')[:-1]

ARCHIVOS_EJECUCION = sorted(ARCHIVOS_EJECUCION, key=len)

# Tipo_solucion==1 -> Solution ineficiente
# Tipo_solución==0 -> Solution eficiente
tipo_solucion = 0
m_juego = 'p'

print(ARCHIVOS_EJECUCION)

archivo_escritura = f'estudiante/eficiencia/datos_ejecuciones/datos_{m_juego}_{tipo_solucion}.csv'

cabecera = list(range(MIN_LETRAS, MAX_LETRAS + 1))

cabecera.insert(0, "Tamano")

with open(archivo_escritura, 'w', newline='') as csvfile:
    writer = csv.DictWriter(csvfile, fieldnames=cabecera)
    writer.writeheader()

    for archivo in ARCHIVOS_EJECUCION:
        diccionario = './data_eficiencia/' + archivo

        ejecucion = f"/home/daniel/Proyectos/ED/P4/cmake-build-release/test_eficiencia {diccionario} data/letras.txt {m_juego} {tipo_solucion} "

        # print(ejecucion)
        r = envoy.run(ejecucion)

        a = r.std_out

        a = a[:-1]

        datos = a.split(';')

        datos.insert(0, archivo[12:-4])

        d = dict(zip(cabecera, datos))

        # print (d)

        writer.writerow(d)
