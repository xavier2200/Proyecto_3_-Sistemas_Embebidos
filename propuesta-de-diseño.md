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
 ![Diagrama de funciones](./diagramas/functional_diagram_smcei.mmd)

 # Arquitectura de hardware y software utilizadas

 ![Diagrama de hardware](./diagramas/hardware_architecture_esp32.mmd)

 ![Diagrama de software](./diagramas/software_architecture_esp32.mmd)