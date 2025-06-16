# Propuesta de Diseño: Monitor de Consumo Energético en Tiempo Real

## Aplicación a Desarrollar

**Sistema de Monitoreo y Control Energético Inteligente (SMCEI)** - Monitor de consumo energético en tiempo real para electrodomésticos, escalable para uso en toda la casa. Este sistema está específicamente enfocado a zonas rurales y comunidades de Costa Rica donde los sistemas de producción energética son limitados (micro-redes, generadores diesel, sistemas solares aislados), por lo cual es necesario hacer un uso racionado y optimizado de los recursos energéticos disponibles.

## Contexto del Problema en Costa Rica

- Zonas rurales remotas con generadores comunitarios de 3-8kW
- Sistemas solares residenciales con baterías limitadas (5-15kWh)
- Micro-redes comunitarias que abastecen 5-20 familias
- Territorios indígenas con acceso energético precario
- Comunidades costeras dependientes de generadores diesel

## Requerimientos del Sistema

### Requerimientos Funcionales Principales

El sistema debe realizar lo siguiente:

**RF01: Realizar monitoreo continuo de potencia consumida por cargas individuales o conjunto de cargas**
- Medición de potencia real (P) con precisión ±3%
- Medición de voltaje RMS (110V-240V) con precisión ±2%
- Medición de corriente RMS (0-30A) con precisión ±3%

**RF02: Capacidad de emitir alertas configurables cuando la potencia supere valores definidos por el usuario**
- Alertas visuales (LCD parpadeante, LEDs)
- Alertas sonoras (buzzer configurable)
- Múltiples niveles de alerta (precaución, advertencia, crítico)

**RF03: Capacidad de recolectar, almacenar y transmitir datos para análisis posterior**
- Almacenamiento local de mínimo 7 días de datos
- Transmisión vía WiFi/LoRa a servidor central
- Datos incluyen: consumo por hora, picos de demanda, patrones de uso

**RF04: Capacidad de reaccionar automáticamente ante sobrecarga desconectando la carga**
- Detección de sobrecarga en tiempo real (≤100ms)
- Desconexión automática mediante relé de control (≤200ms)
- Reconexión inteligente cuando condiciones se normalicen

**RF05: Visualización en tiempo real de lecturas en display LCD**
- Potencia actual, voltaje, corriente
- Energía acumulada del día
- Estado del sistema y alertas activas
- Interfaz en español con iconografía intuitiva

### Requerimientos de Tiempo Real Críticos

- **RTR01:** Muestreo de señales eléctricas cada 10ms (determinístico)
- **RTR02:** Detección de condiciones de sobrecarga ≤ 100ms
- **RTR03:** Ejecución de desconexión de emergencia ≤ 200ms
- **RTR04:** Actualización de display ≤ 500ms
- **RTR05:** Respuesta a comandos de usuario ≤ 1 segundo

## Concepto de Operaciones - Monitor de Consumo Energético

### Perspectiva del Usuario Final

**¿Qué es y para qué sirve?**
Es un dispositivo inteligente que se instala en el centro de carga de cualquier hogar o edificación o también se puede colocar entre el toma corriente y cualquier electrodoméstico para mostrar cuánta electricidad está consumiendo en tiempo real. Diseñado especialmente para familias rurales de Costa Rica que tienen electricidad limitada (solar, generador comunitario, etc.).

### Operación Diaria Típica

#### Por la mañana:
- El usuario se acerca al dispositivo y ve en la pantalla cuánta energía se está consumiendo actualmente
- Conecta electrodomésticos prioritarios (refrigerador, luces) viendo el consumo en tiempo real
- El sistema muestra con colores simples: verde (consumo normal), amarillo (precaución), rojo (límite)

#### Durante el día:
- Antes de conectar cualquier aparato nuevo, el usuario verifica en pantalla si puede hacerlo sin sobrecargar el sistema
- Si intenta usar demasiados aparatos, el sistema emite una alerta sonora y visual antes de que se dañe algo
- Puede ver cuánta energía ha usado y cuánta le queda para el resto del día

### Funciones automáticas que ayudan al usuario:
- **Protección automática:** Si hay sobrecarga, desconecta automáticamente antes de que se dañen los aparatos o el sistema eléctrico
- **Alertas inteligentes:** Avisa cuando está cerca del límite de consumo

### Beneficios prácticos para el usuario:
- **Ahorro de dinero:** Evita desperdiciar combustible del generador, agotar baterías solares o simplemente reducir la cuenta mensual
- **Protección de aparatos:** Previene daños por sobrecargas eléctricas
- **Tranquilidad:** Sabe exactamente cuánta electricidad puede usar sin problemas
- **Mejor planificación:** Puede decidir qué aparatos usar y cuándo, según su consumo real

### Interfaz simple:
- Pantalla con números grandes y claros
- Indicadores de colores fáciles de entender
- Mensajes en español
- Botones simples para configurar límites personalizados

Este sistema convierte el manejo de electricidad limitada de una preocupación constante en una tarea simple y controlada.

# Diagrama de funciones del sistema
 ```mermaid
flowchart TD
    SMCEI["🏠 SISTEMA SMCEI<br/>Monitor de Consumo Energético"]
    
    %% Funciones principales simplificadas
    subgraph MEDIR ["⚡ MEDIR"]
        F1["📊 Medir Corriente<br/>y Voltaje"]
        F2["⚙️ Calcular Potencia<br/>y Energía"]
    end
    
    subgraph PROTEGER ["🛡️ PROTEGER"]
        F3["🚨 Detectar<br/>Sobrecarga"]
        F4["⚡ Desconectar<br/>Automáticamente"]
        F5["🔄 Reconectar<br/>Cuando sea Seguro"]
    end
    
    subgraph MOSTRAR ["📱 MOSTRAR"]
        F6["📺 Mostrar Datos<br/>en Pantalla"]
        F7["💡 Alertas Visuales<br/>y Sonoras"]
        F8["⌨️ Recibir Comandos<br/>del Usuario"]
    end
    
    subgraph COMUNICAR ["📡 COMUNICAR"]
        F9["📶 Enviar Datos<br/>por WiFi"]
        F10["📡 Transmitir por<br/>LoRa (Opcional)"]
    end
    

    
    subgraph GESTIONAR ["⚙️ GESTIONAR"]
        F13["🔧 Configurar<br/>Parámetros"]
        F14["🔄 Mantener<br/>Sistema"]
    end
    
    %% Conexiones principales del sistema
    SMCEI --> MEDIR
    SMCEI --> PROTEGER
    SMCEI --> MOSTRAR
    SMCEI --> COMUNICAR
    SMCEI --> GESTIONAR
    
    %% Flujo principal de operación
    F1 --> F2
    F2 --> F3
    F3 -->|"Sobrecarga<br/>Detectada"| F4
    F4 --> F7
    F4 --> F5
    
    %% Flujos de datos
    F2 --> F6
    F2 --> F9
    F2 --> F10
    
    %% Flujos de usuario
    F8 --> F13
    F13 --> F6
    
    %% Flujos de mantenimiento
    F14 --> F6
    F14 --> F7
    
    %% Tiempos críticos (simplificados)
    F1 -.->|"10ms"| F2
    F3 -.->|"<100ms"| F4
    F4 -.->|"<200ms"| F7
    
    %% Estilos simplificados
    classDef medir fill:#e3f2fd,stroke:#1565c0,stroke-width:2px
    classDef proteger fill:#fce4ec,stroke:#c2185b,stroke-width:2px
    classDef mostrar fill:#e8f5e8,stroke:#2e7d32,stroke-width:2px
    classDef comunicar fill:#fff3e0,stroke:#f57c00,stroke-width:2px
    classDef gestionar fill:#e0f2f1,stroke:#00695c,stroke-width:2px
    classDef sistema fill:#ffebee,stroke:#d32f2f,stroke-width:3px
    
    class SMCEI sistema
    class F1,F2 medir
    class F3,F4,F5 proteger
    class F6,F7,F8 mostrar
    class F9,F10 comunicar
    class F13,F14 gestionar

 ```

 # Arquitectura de hardware y software utilizadas

 ```mermaid
 flowchart TD
    subgraph EXTERNAL ["🔌 CONEXIONES EXTERNAS"]
        GRID["⚡ Red Eléctrica"]
        LOAD["🏠 Electrodoméstico"]
        USER["👤 Usuario"]
        WIFI["🌐 WiFi"]
    end
    
    subgraph ESP32_SYSTEM ["🎛️ ESP32 + COMPONENTES"]
        ESP32["🔷 ESP32<br/>Controlador Principal"]
        
        subgraph SENSORS ["📊 SENSORES"]
            V_SENSOR["📈 Sensor Voltaje"]
            I_SENSOR["📊 Sensor Corriente"]
        end
        
        subgraph INTERFACE ["📱 INTERFAZ"]
            LCD["📺 LCD 16x2"]
            LEDS["💡 LEDs<br/>🔴🟡🟢"]
            BUZZER["🔊 Buzzer"]
            BUTTON["⌨️ Botón"]
        end
        
        PSU["🔋 Fuente 5V"]
    end
    
    %% Conexiones externas
    GRID --> V_SENSOR
    GRID --> I_SENSOR
    I_SENSOR --> LOAD
    USER --> BUTTON
    LCD --> USER
    LEDS --> USER
    BUZZER --> USER
    ESP32 -.-> WIFI
    
    %% Conexiones internas
    V_SENSOR --> ESP32
    I_SENSOR --> ESP32
    ESP32 --> LCD
    ESP32 --> LEDS
    ESP32 --> BUZZER
    BUTTON --> ESP32
    PSU --> ESP32
    PSU --> LCD
    
    %% Especificaciones básicas
    V_SENSOR -.->|"0-250V AC"| ESP32
    I_SENSOR -.->|"0-30A AC"| ESP32
    ESP32 -.->|"WiFi 2.4GHz"| WIFI
    
    %% Estilos
    classDef external fill:#ffcdd2,stroke:#c62828,stroke-width:2px
    classDef esp32 fill:#e1f5fe,stroke:#0277bd,stroke-width:3px
    classDef sensor fill:#e8f5e8,stroke:#2e7d32,stroke-width:2px
    classDef interface fill:#fff3e0,stroke:#f57c00,stroke-width:2px
    classDef power fill:#f3e5f5,stroke:#7b1fa2,stroke-width:2px
    
    class GRID,LOAD,USER,WIFI external
    class ESP32 esp32
    class V_SENSOR,I_SENSOR sensor
    class LCD,LEDS,BUZZER,BUTTON interface
    class PSU power
 ```

 ```mermaid
 flowchart TD
    subgraph ESP32_SW ["🎛️ SOFTWARE ESP32"]
        subgraph TASKS ["🔄 TAREAS PRINCIPALES"]
            TASK_SENSOR["📊 Tarea Sensores<br/>• Leer voltaje/corriente<br/>• Cada 10ms"]
            TASK_CONTROL["🛡️ Tarea Control<br/>• Calcular potencia<br/>• Detectar sobrecarga"]
            TASK_DISPLAY["📱 Tarea Display<br/>• Actualizar LCD<br/>• Controlar LEDs/Buzzer"]
            TASK_WIFI["📡 Tarea WiFi<br/>• Enviar datos<br/>• Conectar internet"]
        end
        
        subgraph FUNCTIONS ["⚙️ FUNCIONES BÁSICAS"]
            FUNC_MEASURE["📏 Medir<br/>V, I, P"]
            FUNC_PROTECT["🛡️ Proteger<br/>Sobrecarga"]
            FUNC_SHOW["📺 Mostrar<br/>Datos"]
            FUNC_SEND["📤 Enviar<br/>WiFi"]
        end
        
        FREERTOS["🔄 FreeRTOS<br/>Sistema Operativo"]
    end
    
    subgraph DATA_FLOW ["📊 FLUJO DE DATOS"]
        SENSORS_DATA["📊 Datos Sensores"]
        POWER_DATA["⚡ Datos Potencia"]
        DISPLAY_DATA["📺 Datos Display"]
        WIFI_DATA["📡 Datos WiFi"]
    end
    
    %% Flujo principal
    TASK_SENSOR --> SENSORS_DATA
    SENSORS_DATA --> TASK_CONTROL
    TASK_CONTROL --> POWER_DATA
    POWER_DATA --> TASK_DISPLAY
    POWER_DATA --> TASK_WIFI
    TASK_DISPLAY --> DISPLAY_DATA
    TASK_WIFI --> WIFI_DATA
    
    %% Conexión con funciones
    TASK_SENSOR --> FUNC_MEASURE
    TASK_CONTROL --> FUNC_PROTECT
    TASK_DISPLAY --> FUNC_SHOW
    TASK_WIFI --> FUNC_SEND
    
    %% Base del sistema
    TASKS --> FREERTOS
    FUNCTIONS --> FREERTOS
    
    %% Timing crítico
    TASK_SENSOR -.->|"10ms"| TASK_CONTROL
    TASK_CONTROL -.->|"<100ms"| TASK_DISPLAY
    
    %% Estilos
    classDef task fill:#e3f2fd,stroke:#1565c0,stroke-width:2px
    classDef function fill:#e8f5e8,stroke:#2e7d32,stroke-width:2px
    classDef data fill:#fff3e0,stroke:#f57c00,stroke-width:2px
    classDef os fill:#f3e5f5,stroke:#7b1fa2,stroke-width:2px
    classDef critical stroke:#d32f2f,stroke-width:3px
    
    class TASK_SENSOR,TASK_CONTROL,TASK_DISPLAY,TASK_WIFI task
    class FUNC_MEASURE,FUNC_PROTECT,FUNC_SHOW,FUNC_SEND function
    class SENSORS_DATA,POWER_DATA,DISPLAY_DATA,WIFI_DATA data
    class FREERTOS os
    class TASK_SENSOR,TASK_CONTROL critical
```