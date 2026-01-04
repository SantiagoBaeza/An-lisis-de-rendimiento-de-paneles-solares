#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Estructura que representa un dato del panel
typedef struct {
    float voltage;
    float current;
    float radiation; 
    int32_t next_index;  // índice del próximo dato (-1 si no hay más)
} Data;

int main() {
    FILE* file = fopen("pv_data.dat", "rb");
    if (!file) {
        perror("No se pudo abrir el archivo pv_data.dat");
        return 1;
    }

    // Paso 1: Leer header y los índices iniciales
    uint32_t header_raw;
    int32_t start_panel1, start_panel2;

    fread(&header_raw, sizeof(uint32_t), 1, file);
    fread(&start_panel1, sizeof(int32_t), 1, file);
    fread(&start_panel2, sizeof(int32_t), 1, file);

    // Paso 2: Separar los valores del header usando máscaras y desplazamientos
    uint16_t total_count = header_raw & 0x3FF;              // últimos 10 bits
    uint16_t height  = (header_raw >> 10) & 0x7FF;       // 11 bits del medio
    uint16_t width   = (header_raw >> 21) & 0x7FF;       // primeros 11 bits

    printf("Total count: %u\n", total_count);
    printf("Panel height: %u\n", height);
    printf("Panel width: %u\n", width);
    printf("Start index panel 1: %d\n", start_panel1);
    printf("Start index panel 2: %d\n", start_panel2);

    // Paso 3: Reservar memoria para los datos
    Data* data_array = malloc(sizeof(Data) * total_count);
    if (!data_array) {
        fprintf(stderr, "Error al reservar memoria para los datos.\n");
        fclose(file);
        return 1;
    }

    // Paso 4: Leer todos los datos en el array
    fread(data_array, sizeof(Data), total_count, file);
    fclose(file);  // ya no necesitamos el archivo

    //calculo el area de los paneles
    float area_panel = (height * width);

    // Paso 5: Recorrer los datos del panel 1
    printf("\n--- Panel 1 ---\n");
    int index = start_panel1;
    float mayor1, menor1;
    int contador1=0;

    while (index != -1) { //este while se repite guardando los datos en estructuras en cada iteracion hasta que next_index sea -1
        Data actual = data_array[index];
        printf("Voltage: %.2f, Current: %.2f, Radiation: %2.f\n", actual.voltage, actual.current, actual.radiation);
        index = actual.next_index;

        //calculo el rendimiento para esta iteracion
        float area_por_radiacion= area_panel * actual.radiation;
        float tension_por_corriente= actual.current* actual.voltage;
        float rendimiento = (tension_por_corriente / area_por_radiacion)*100;
        printf("El rendimiento es: %2.f\n", rendimiento);
        if(contador1==0){
            mayor1=rendimiento;
            menor1=rendimiento;
        }else{
            if(mayor1<rendimiento){//si el rendimiento mas grande es menor al rendimiento actual...
                mayor1=rendimiento;
            }else if(menor1>rendimiento){//si el rendimiento mas chico es mayor al rendimiento actual...
                menor1=rendimiento;
            }
        }
        contador1++;
    }
    printf("El mayor rendimiento del panel 1 fue: %2.f, y el menor rendimiento fue: %2.f\n", mayor1, menor1);

    // Paso 6: Recorrer los datos del panel 2
    printf("\n--- Panel 2 ---\n");
    index = start_panel2;
    float mayor2, menor2;
    int contador2=0;
    while (index != -1) {
        Data actual = data_array[index];
        printf("Voltage: %.2f, Current: %.2f, Radiation: %2.f\n", actual.voltage, actual.current, actual.radiation);
        index = actual.next_index;
        
        //calculo el rendimiento para esta iteracion
        float area_por_radiacion= area_panel * actual.radiation;
        float tension_por_corriente= actual.current* actual.voltage;
        float rendimiento = (tension_por_corriente / area_por_radiacion)*100;
        printf("El rendimiento es: %2.f\n", rendimiento);
        if(contador2==0){
            mayor2=rendimiento;
            menor2=rendimiento;
        }else{
            if(mayor2<rendimiento){//si el rendimiento mas grande es menor al rendimiento actual...
                mayor2=rendimiento;
            }else if(menor2>rendimiento){//si el rendimiento mas chico es mayor al rendimiento actual...
                menor2=rendimiento;
            }
        }
        contador2++;
    }
    printf("El mayor rendimiento del panel 2 fue: %2.f, y el menor rendimiento fue: %2.f\n", mayor2, menor2);

    // Liberar memoria
    free(data_array);
    return 0;
}
