#define REC_UART 1<<0//Rec
#define SEND_UART 1<<1 //допустим, что это бит, который запустит передачу данных
#define MISS_UART 1<<2 //Miss
#define MAX_RECEIVED_UART_WAIT_TIME 1000
#define MAX_INPUT_STR_LENGTH 100
#define TERM '\0' //символ окончания строки данных
#define ERROR 0
#define OK 1

//----------------------------------------------------------

char inputUARTString [MAX_INPUT_STR_LENGTH];

void main
{
	
	int strLength =  SerialReceive(inputUARTString,MAX_INPUT_STR_LENGTH);// вызываем функцию приёма данных
}
//----------------------------------------------------------

//----------------------------------------------------------
//функция передачи данных по UART
//str-указатель на передаваемую строку символов
int SeiralTransmitStr(char * str)
{
	int dataTransamitWaiteTime;//переменная для хранения времени ожидания передачи одного символа по UART
	
	for(int i=0; str[i]!=TERM; i++)
	{
		//отправляем элемент строки с номером i на передачу по UART
		UARTTransitReg = str[i];
		
		//сообщаем контроллеру UART, что данные необходимо отправить
		UARTStatusRegister = UARTStatusRegister|SEND_UART;//а если надо было обнулить бит, то можно так UARTControlReg = UARTControlReg&(~START_TRANSMIT_UART);
		
		//ждём, пока не закончится передача str[i] 
		dataTransamitWaiteTime = 0;//обнулили переменную - счётчик времени передачи одного символа по UART
		while( (UARTStatusRegister & SEND_UART != 0)&&              //пока данные не отправились и
		       (dataTransamitWaiteTime<MAX_RECEIVED_UART_WAIT_TIME))//пока время ожидания не превысило максимального
		{                                                           //ждём
			dataTransamitWaiteTime++;                               //пока ждём, инкрементируем переменную - счётчик времени
		}
		
		if(dataReceiveWaiteTime>=MAX_RECEIVED_UART_WAIT_TIME)//если произошло событие переполнения переменной-счётчика циклов ожидания приёма байта данных
		   {
		         return ERROR;  
		   }
		                                      
	
	}
	return OK;
}
//----------------------------------------------------------

//----------------------------------------------------------
//функция возвращает количество принятых байт данных (значение maxStrLength - длина массива str)
int SerialReceive(char *str, int maxStrLength)
{
	int dataReceiveWaiteTime;//переменная для хранения времени ожидания приёма одного символа по UART
	
	for(int i = 0; i<=maxStrLength; i++)
	{
		dataReceiveWaiteTime = 0;//обнулили переменную - счётчик времени приёма одного символа по UART
		while(((UARTStatusRegister&REC_UART)==0)&&//Ждем до тех пор, покаы в регистре Status  не будет выставлен флаг Rec (приняты данные их можно загрузить) и
		       (dataReceiveWaiteTime`<MAX_RECEIVED_UART_WAIT_TIME))//пока переменная-счётчик итераций цикла ожидания не достигнет максимального значения
		{                                                          // ждём
			dataReceiveWaiteTime++;                                 // пока ждём инкрементируем переменную-счётчик
		}
		
		if(dataReceiveWaiteTime>=MAX_RECEIVED_UART_WAIT_TIME)//если произошло событие переполнения переменной-счётчика циклов ожидания приёма байта данных
			return i;                                        
	
		str [i]= UARTReceived;//&0x0000000FF;
				
	}
	return i;
}
//----------------------------------------------------------



void startTIMER (int tmr, int count, int divider)
