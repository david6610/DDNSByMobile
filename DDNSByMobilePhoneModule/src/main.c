/*****************************************************************************************************
 @project name: cosmos
 @system:       nOS with uIP1.0	
 @funcation: 	TCP/IPתRS485  socket=10
 @bug:          jerkoh@163.com
 @date:         2013-02
     stress tests: 
                   ���Ի���: ����1~25��C
                   ���ػ�: ATOM D425��2G�ڴ�
			       USB����: RD9700 USB2.0 To Fast Ethernet Adapter  
			       ������: Mercury-S108M
			       ��������MDK-4.12
	
                   Tcp/ip client ÿ1ms ����32Kbytes,server����32Kbytes���� (����2��Tcp client
                   ͬʱ����)������2��icmp echo,1��webserverÿ1s ˢ��һ��,
			       �������ϵ����5��,��������������ϵͳ���������������client��ʱ��������server
			       (ע������Mss��RAM���⡢����ÿ1ms�շ�32Kbytes���ݱض��ж�������,����Ӱ��ѹ��
			       ����) 
      disclaimer��
			       ����Э��ջ�����������ļ�����Դ������.
			       Ӧ��APP�������Դ,Ӧ��APP������ڲ���������ͬ��������������ҵ�����ҵ��
			       Ŀ�ĵ�Ӧ�ã�������Ӧ�����漰�������Ʋ���ȫ�Ĺ���,��ҽ�ơ����¡����յ���Ŀ,
				   �κ���ʹ��cosmos������ɵĲ������,���߲��е��κη�������
 ---------------------------------------------------------------------------------------------------- 
 R1.50 2014-11-28	��DNS ��DNS�ܹ�����WEB/EMAIL SMTP����Ӧ webclient �� smtp;  ��������ȫ��ͨ��
 ---------------------------------------------------------------------------------------------------- 
 R1.40 2014-11-26	�޶��� webclient / smtp ͬʱ���г��ֵ� 1)DNS��������[0.0.0.0] ���⣻   2)APPCALL����
                    3)������smtp �� DNS ��������
					��ע�⡿�е��������볤�ȣ��������ȵĲ���Ҫ����ȡ����
 ---------------------------------------------------------------------------------------------------- 
 R1.31 2014-10-25	�޶��� DNS ���� resolv_lookup(char *name) BUG
 ---------------------------------------------------------------------------------------------------- 
 R1.31 2014-10-19	����SMTP���ܱ���ͨ��
 ---------------------------------------------------------------------------------------------------- 
 R1.3  2014-10-17	�������߶�������ɣ�ӡˢ��P2 pin9,p10,CPU�ܽ� PB12)
 ---------------------------------------------------------------------------------------------------- 
 R1.1  2014-09-25	EEPROM�洢����д�����ɹ����
 ---------------------------------------------------------------------------------------------------- 
 R1.0  2014-09-25	GSM��DNS��webclient���״�ȫ�̲���ͨ��
                    �Ż�������Ҫ��flash ģ�� eeprom �洢 ���ò�����
						1����վ��3������������� ���洢
						2����Ȩ���ֻ��ţ�������� ���洢
						3��������ַ�Ƿ���Ҫ����  DHCP����
 ---------------------------------------------------------------------------------------------------- 
 DV1.0 2014-09-20	DNS��webclient �������� ������ַ������ɣ�
                    ֧���������ӣ�1����������TCP  2�����Ի�ȡ����IP��ַ����վ
	                �޶��ˣ� V1.b  2013-03-11 : #define UIP_CONF_MAX_CONNECTIONS 2  
 ---------------------------------------------------------------------------------------------------- 
 DV0.9 2014-08-30	GSM���ܽ��ա��������ܳ������  
 ---------------------------------------------------------------------------------------------------- 
 DV0.0  2013-02-18 	1) Ӳ���忪������Դ��
	                   http://item.taobao.com/item.htm?spm=a1z10.1.w4004-3800642413.2.iENfgU&id=18937166030
 					2) GSM ���ŷ��Ͱ���Դ��
    	               http://detail.tmall.com/item.htm?id=37785010396&spm=a1z09.2.9.237.GXXwBd&_u=q36efgg6b64&mt=
 					3) ���ù��ߡ����Թ��ߣ�(����ܸ�����������л ��������)
					   http://shop61791934.taobao.com
					   http://www.cnblogs.com/wenziqi/
					   http://www.smartmcu.com
 					4) ��װ��������Դ��
					   http://item.taobao.com/item.htm?spm=a1z09.2.9.12.hFLNQn&id=2208931068&_u=q36efgg7e6e
                    5) BASE64 �㷨Դ�����ԣ�
					   http://www.cnblogs.com/syxchina/archive/2010/07/25/2197388.html
					
 ====================================================================================================
 logs: alpha=V0.x  beta=V1.x  Release>=V2.0	  	 ������صĵ��Ժ�������global.h  ***debug define***
 ----------------------------------------------------------------------------------------------------
 V2.0  2013-xx-xx  Release                    
 ----------------------------------------------------------------------------------------------------
 V1.f  2013-xx-xx                     
 ----------------------------------------------------------------------------------------------------
 V1.e  2013-03-14  ���������еı���������(����warning=<unspecified> ��level0(-o0))
                   �����˲���debug�����Ϣ
				   ������UIP_STATIC_IP_ADDR�궨����þ�̬IP��̬DHCP                     
 ----------------------------------------------------------------------------------------------------
 V1.d  2013-03-13  ������uip1.0��DHCP����,���Գɹ�
                   ע������޸�enc28j60�ĳ�ʼ�����չ㲥���ܼĴ���ERXFCON_BCEN                     
 ----------------------------------------------------------------------------------------------------
 V1.c  2013-03-11  ������uip_main��elseif �ж��������⣬�����V1.b��Bug                   
 ----------------------------------------------------------------------------------------------------
 V1.b  2013-03-11  ʵ���˶��(10��)client���ӵ�server keepalive����	  (ʵ����2����by david)
                   #define UIP_CONF_MAX_CONNECTIONS 10
                   #define UIP_CONF_MAX_LISTENPORTS 10
				   if((socket_keepalive[i].uip_kpl_type==SOCKET_COMM_OFF)&&
				   ((uip_conn->rport==socket_keepalive[i].uip_kpl_rport)))
				   ���ڵ�©���� ĳ��clientһֱ��ͣ�ط����ݸ�uIPջ,uIP��һֱnewdata��Ǵ���
				   �޻�����벢��⵽uip_poll���keepalive������Ҫ�ͷŵ�client                 
 ----------------------------------------------------------------------------------------------------
 V1.a  2013-03-09  ȡ��webserver���й���,ע��80�ڵļ���
                   ɾ����STM32�¶Ⱥ���
                   #define UIP_CONF_MAX_CONNECTIONS 1
                   #define UIP_CONF_MAX_LISTENPORTS 1                     
 ----------------------------------------------------------------------------------------------------
 V1.9  2013-03-08  ��������0,1��len u8�ĳ�u16   
                   ���ڻ����С����С��1500���ĳ�1200����ֹ�ڴ�copy�����hardfault����                
 ----------------------------------------------------------------------------------------------------
 V1.8  2013-03-05  ������T2��ʱ�� 1ms��1.1ms��BUG (ETTG ��������)                  
 ----------------------------------------------------------------------------------------------------
 V1.7  2013-03-04  �����˲������ƶ���
                   ʵ����TCP Serverģʽ��keepalivetime����,Socket�������10��
				   keepalive ��Զ�̿ͻ����½����Ӻ󡢻���ͨ�Ź�һ�κ󳬹����õı���ʱ��
				   ���������Զ��Ͽ��ͷŸÿͻ���(ֻ�ܿ�һ��socket��ģʽ��Ч
				   #define UIP_CONF_MAX_CONNECTIONS 1) �����޷�ȷ���ĸ�client������uip
				   _abort()����Ͽ�client
 ----------------------------------------------------------------------------------------------------
 V1.6  2013-03-03  ������web�����ݷ���״̬Ǩ�Ʊ���(html_status δ�궨��ʵ��)
				   webserver���ڸ��ʽϵ͵��Զ�ˢ�´���
				   POST����δ����
				   ����Ұ��Ƕ��ʽ�����ҵ�STM32�ڲ��¶�ֵ�������
 ----------------------------------------------------------------------------------------------------
 V1.5  2013-03-02  main.c δ���д��������鵵
                   RAM �ܼ�20K
                   ����10K��RAM����UART1&2,�����궨��ֵ�����޸�UART�Ļ����շ�����
				   ���ͷŴ����ڴ湩�û�����ʹ��
                   ����STM32 ����Ӳ����,ʵ����main��0,��ʱ�����
				   Ӳ����ʱ����0,��֤��mainĳ����ѭ���������붨ʱ��
				   ���߶�ʱ�������С�main����������¶����Խ���ϵͳ��λ
                   ����������δ����,�����ľ��涼δ����
				   TCP Serverģʽ��keepalive�����Ͽ���ʱ��client����δ����(������BUG)
				   uip1.0Э��ջ����Ϣ��ӡδ�궨�嵽usart1 
				   ����1��USART1 CMD��TCP CLINET����: ~Cosmos Restart~ =ϵͳ��λ
				   (�ɹ�����TCP���Ӳ������շ����������Ч)     
 ----------------------------------------------------------------------------------------------------
 V1.4  2013-03-01  ������һ���򵥵�webserver����,����ReplaceStr��������ǿ��˵��
                   caNewString[1024];����ȫ��	
                   ���ڲ���HTML�Ķ�̬�����޸�
				   ������MAC��ַ��*Ψһ*���㷨(ע�Ⲣ��100%Ψһ,������������дMAC)
				   ����web��ϵͳ��������ʱ��(����ȷ?)
 ----------------------------------------------------------------------------------------------------
 V1.3  2013-02-26  uIP1.0�ں��޸ģ�UIP_TIMER����µĴ���
                   ԭ��0.5sһ�θĳ�10msһ�κ�,uIP��Ӧ����ҲҪ����50��
                    static u8_t uip_reasstmr;      �ĳ� static u16_t uip_reasstmr;
                   (ԭ��u8_t<=255,ϵͳ��Ҫ40*50��ֵ���Ըĳ�u16_t)
				   #define UIP_REASS_MAXAGE 40    �ĳ� #define UIP_REASS_MAXAGE 40*50
				   ������V1.1 timer_expired(&periodic_timer)����������
				   �����˰汾�Ŀɱ�������DEBUG���
 ----------------------------------------------------------------------------------------------------
 V1.2  2013-02-26  ͨ���ײ�enc28j60 send����������V1.0�汾��enc28j60��������
                   (1ms�ͻ��˷���������,����������lookback����,ͬʱ����icmp
				   ͨ�����׵���EIR_TXERIF����ķ���)
				   �������ݵ�ͨ��ʱ,ICMP��ʧ�ʽϸ�
 ----------------------------------------------------------------------------------------------------
 V1.1  2013-02-25  �޸�timer_expired(&periodic_timer) ԭ��500msִ��һ��
                   �ָĳ�500/50 msһ��ִ��һ�� Ŀ����Ϊ�˿ͻ��������������̵ȴ�ʱ��
				   ��uip���ں���Ӧ����ʱ��Ҳ��500ms���10msһ������,ע��ARP�ϻ�����
				   δ�仹��10sһ��
				   Uip_Appcall(����rport�ı�������),��keepaliveʹ��,��connected��ʱ��
				   �޷�����conn�ľ���rport����connֵ,����uIP1.0�����ʺ���server������
				   ����һЩ�������ϴ����ݲ���.
 ----------------------------------------------------------------------------------------------------
 V1.0  2013-02-23  �����˲��ִ���Ķ��壬beta�汾V1.0
                   ʵ���˳�ʱ��������ݵ�TCP->RS485���͹���,����10GB�����޴���
				   δʵ��TCP Server��conn�� keepalive����(socket �����ɹ�
				   ���Ӻ���ָ��ʱ����δ�����շ�����,�����������ر�Socket
				   Ŀ��,��ֹclient�˴�������Ӻ�,���������ݽ���,���ķ�һ����Դ)
				   ��ʵ����RJ45�ĶϿ����,��δ����socket�������ر�
				   δʵ��ʵʱ�Ľ�RS485�ڽ����ݷ��͵�TCP Socket(���н�����
				   socket�������һ��ͨ�ŵ�socket)
				   enc28j60 EIR_TXERIF����δ���,����ʼ��enc28j60��ʱ���
				   ���socket clientͬʱ����tcp/ip���ݽ���,uIP1.0��������ͨ��
				   ���׶�ʧ��
				   1ms�ͻ��˷���������,����������lookback����,ͬʱ����icmpͨ��
				   ���׵���EIR_TXERIF����ķ���
				   ����Beta Release �汾�����ӹ��ܰ������¹���:
				   01.WebServer  02.tcp client 03.udp server 04.udp client
				   05.keepalive  06.udp broadcast search 07.flash save 08.dhcp      
				   09.telnet     10.tftp upgrade  11.Change the baud rate
 ----------------------------------------------------------------------------------------------------
 V0.5  ------V0.F  null 
 ----------------------------------------------------------------------------------------------------
 V0.4  2013-02-23  ����limit retrieve length   len-1�Ĵ���ᵼ��mss=1446ʱ�ְ�
				   536,@enc28j60PacketReceive
				   �ײ���������ȫ���������
 ----------------------------------------------------------------------------------------------------
 V0.3  2013-02-22  ����Enc28j60_EREVID����Ϣ���,�ر�ENC28J60��ʼ���ж�ʹ��
                   ����BUG pc�����ݰ�1ms���͸�Enc28j60,����OK,��ENC28J60
				   �ײ㷢�ͺ�������BUG. 
				   ������1.ECON1_TXRTS�ĳ�ECON1_TXRST,������Ȼ����
 ----------------------------------------------------------------------------------------------------
 V0.2  2013-02-21  ���uIP1.0����ֲ,enc28j60�ײ�������ICMP =:)
                   Debug����1��� =:)
 ----------------------------------------------------------------------------------------------------
 V0.1  2013-02-20  ��������ֲ���� alpha�汾V0.1	
                   T410 Intel(R) 82577LM Gigabit Network Connection
				   ʹ�ý����߿���ENC28J60���� ping

                   �ο���ֲ������Ӳ����Դ��Դ����;�������£�
                   (1)uIP1.0 Adam Dunkels adam@dunkels.com
				   (2)GPL V2 Guido Socher
				   (3)(C)COPYRIGHT 2011 Ұ��Ƕ��ʽ����������
				   (4)STMicroelectronics.
				   (5)Microchip TCP/IP
				   (6)j60 code+protues v1 
 ----------------------------------------------------------------------------------------------------
 V0.0  2013-02-18  ȷ��ʹ�õ�Ӳ���忪���� ��Դ��
                   http://item.taobao.com/item.htm?spm=a1z10.1.w4004-3800642413.2.iENfgU&id=18937166030
 ----------------------------------------------------------------------------------------------------                  
****************************************************************************************************/

/*! \file stm-tcp main.c
 *	\brief the main function.
 */

#include "global.h"
#include "stdio.h"
//#include "eeprom.h"
#include "getIPdategram.h"
#include "uip1.0\apps\webclient\webclient.h"
#include "uip1.0\apps\webclient\webclient-strings.h"
#include "uip1.0\apps\resolv\resolv.h"
#include "uip1.0\uip\uiplib.h"
#include "uip1.0\apps\smtp\smtp-strings.h"

char Vxy[]="beta v1.e";											   //�ı�Beta V1.x���ɸı�Debug����Ĵ�ӡ��Ϣ
char fw_version[]="[system info]:firmware =~VvEeRrSsIiOoNn~ \r\n"; //ע��~VvEeRrSsIiOoNn~ʵ���Ǳ����ַ�
                                                                   //����Vxy[],Ӧ��string�����滻���ܵĺ���
																   //Ŀ�Ľ�����ReplaceStr����,��ʵ������

unsigned char  lasted_compiled_system_date[]="" __DATE__;	       //����������
unsigned char  lasted_compiled_system_time[]="" __TIME__;	       //������ʱ��



struct timer periodic_timer, arp_timer;

struct uip_tcp_socket_keepalive {
  unsigned int  uip_kpl_rport;
  unsigned int  uip_kpl_time;
  unsigned int  uip_kpl_type;
};
struct 	uip_tcp_socket_keepalive socket_keepalive[UIP_CONNS];      //���屣�ʱ��

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

#ifndef NULL
#define NULL (void *)0
#endif /* NULL */

//����������������������������������������������������������������������������������������������������������������������������������������������������������������
#define CONNECT				TRUE
#define DISCONNECT 			FALSE;

#ifndef REMOTE_PORT										//Զ�̽ӿڶ���
#define REMOTE_PORT 		1024
#endif 


#define GSM_ONLY_R_W_EN_SM 	0							// ֻ��дӢ�Ķ���

#define CMD_Q_MAX			5					       //���ſ�����������ܷ��ö��������ţ������ڼ�����Ϊ5��
#define SIM_Q_MAX			10					       //���ſ�����������ܷ��ö��������ţ������ڼ�����Ϊ5��


#define UART_RETURN_OK		"Correct\r\n"
#define UART_RETURN_ERR 	"ERROR\r\n"

#define UART_DEBUG_SND_HEAD	"UART1>>======\r\n"
#define UART_DEBUG_SND_END	"=============\r\n"
#define UART_DEBUG_RCV_HEAD	"UART1<<------\r\n"
#define UART_DEBUG_RCV_END	"-------------\r\n"

#define CLIENT_SND_HEAD		"client>>#####\r\n"
#define CLIENT_SND_END		"\r\n###########\r\n"

#define CLIENT_RCV_HEAD		"client<<%%%%%\r\n"
#define CLIENT_RCV_END		"%%%%%%%%%%%%%\r\n"


#define UART_READY0			"RDY\r\n"
#define UART_READY1			"+CFUN: 1\r\n"
#define UART_READY2			"+CPIN: READY\r\n"
#define UART_READY3			"Call Ready\r\n"
#define UART_READY4			"AT\r\n\r\nOK\r\n"



#define AT_CR_LF			"AT\r\n"					//��������
#define N_AT_CR_LF			0							//��������
//	���ö�ȡӢ�Ķ��ŵ�����
#define AT_SetTxtMod		"AT+CMGF=1\r\n"				//�����ı�ģʽ
#define N_AT_SetTxtMod		1							//�����ı�ģʽ
#define AT_SetGSMCharSet	"AT+CSCS=\"GSM\"\r\n"		//����GSM�ַ���
#define N_AT_SetGSMCharSet	2
#define AT_SetSMSHint		"AT+CNMI=2,1\r\n"			//��������Ϣ��ʾ
#define N_AT_SetSMSHint		3
//  
#define AT_SetUCS2CharSet	"AT+CSCS=\"UCS2\"\r\n"		//����UCS2�ַ���
#define N_AT_SetUCS2CharSet	4
#define AT_SetSMSModPara	"AT+CSMP=17,167,2,25\r\n"	//�����ı�ģʽ����
#define N_AT_SetSMSModPara	5
#define AT_ReadSMS			"AT+CMGR="					//��ȡ��**������
#define N_AT_ReadSMS		6
#define AT_Read_UNREAD		"AT+CMGL=\"REC UNREAD\"\r\n"	//��δ�����ж���
#define N_AT_Read_UNREAD	7

#define AT_SndPhone			"AT+CMGS="					//ѡ����ŷ��͵绰����
#define N_AT_SndPhone		8

//#define AT_CheckFeePhone	"AT+CMGS=\"00310030003000380036\"\r\n"		//GSM ͨ�����Ͷ��Ÿ�10086 ��YE�������
//#define N_AT_CheckFeePhone	9							//GSM �ػ�


#define SMS_END_CHAR		0x1A						//���ŷ��ͽ����ַ�

		   
#define AT_DelSMSTstCmd		"AT+CMGD=?\r\n"				//����֧�ֵ�ɾ������Ϣ��������
#define N_AT_DelSMSTstCmd	10
#define AT_DelSMS			"AT+CMGD=40,2\r\n"			//�������40������Ϣ��ɾ���Ѷ��Ķ���Ϣ���ѷ��͵Ķ���Ϣ������δ���͵Ķ���Ϣ
#define N_AT_DelSMS			11


#define RT_RDY					"RDY\r\n"					//������ȷ
#define RT_OK					"OK\r\n"					//������ȷ
#define RT_ERROR				"ERROR\r\n"					//���ش���
#define RT_SM_WaitRd			"+CMTI: \"SM\","		//�����ж��ŵ���ģ ��ʽ ��+CMTI:"SM",**"   ** ��ʾ���֣����Ŵ洢������
#define N_RT_SM_WaitRd			12							//
#define RT_SM_ARRIVE_UNREAD		"+CMGR: \"REC UNREAD\""	//���ŵ������ʼ��ʾ +CMGR:���Ƿ��Ѷ��������绰���롱������������������
#define N_RT_SM_ARRIVE_UNREAD	13							//���ŵ������ʼ��ʾ +CMGR:���Ƿ��Ѷ��������绰���롱������������������
#define RT_SM_ARRIVE_READ		"+CMGR: \"REC READ\""	//���ŵ������ʼ��ʾ +CMGR:���Ƿ��Ѷ��������绰���롱������������������
#define N_RT_SM_ARRIVE_READ		14							//���ŵ������ʼ��ʾ +CMGR:���Ƿ��Ѷ��������绰���롱������������������

#define RT_SM_PRE_UNREAD		"+CMGL: "				//����ѡ����ʱ�Ĵ� +CMGL: 13,"REC UNREAD"
#define N_RT_SM_PRE_UNREAD		15							//
// 

#define RT_SndPrompt		"> "							//������ʾ��
#define N_RT_SndPrompt		16							//������ʾ��
#define RT_Snd_OK			"+CMGS"						//���ͳɹ� +CMGS: Num 

#define RT_RING				"RING\r\n"				//�绰����
#define N_RT_RING			17							//�绰����


#define RT_POWER_OFF		"NORMAL POWER DOWN\r\n"		//GSM �ػ�
#define N_RT_POWER_OFF		18							//GSM �ػ�

#define RT_I_DontKnow		"I Don't Know !\r\n"		//�Է��ص��������ʶ��
#define N_I_DontKnow		250


#define ATH					"ATH\r\n"					//�Ҷϵ绰

#define SND_STATUS			"\r\n> "				//���յ���ʾ���ڷ���״̬���˳���


#define UNICODE_PHONE_LEN	60					//TO:�绰,����
#define UNICODE_SM_LEN		600					//TO:�绰,����


int			 GSM_offline_counter = 0 ;
u8           snd_usart1_array[BUF1_LEN];
u16 volatile snd_usart1_data_len		= 0;
u8 volatile  Uart1SndDataFlag		= 0;

u8 volatile  GSM_active_flag  			= 0;				// GSMģ���ϵ��������ܹ���������ı�־��   
u8 volatile  init_GSM_end_flag   		= 0;				// ��ʼ��GSMģ�� �������			             

u8          tmp_eth_data_array[2*BUF1_LEN];
//----------------------------------------------------								 	  
struct phone {
	char t1[UNICODE_PHONE_LEN];
	char t2[UNICODE_PHONE_LEN];
	char t3[UNICODE_PHONE_LEN];
	char svr[UNICODE_PHONE_LEN];
} phonelist ;

char phoneSets[PARA_ACCOUNT_PHONE][UNICODE_PHONE_LEN];

//------------------------------------------------------
char        requestIPphone[UNICODE_PHONE_LEN] 		= "";	 //�����ȡ��ǰIP��ַ�ĵ绰����
char		EmailSubject[PARA_L_WEB*2];
char		EmailMsg[PARA_L_WEB*2];
//------------------------------------------------------

typedef struct {  	
	char URL[PARA_L_WEB]; 		//web��ַ
	char file[PARA_L_WEB];		// Ҫ GET ���ļ���
	char s_str[PARA_L_WEB];		// ���صĹؼ����У���ʼ�ַ���
	char e_str[PARA_L_WEB];		// ���صĹؼ����У������ַ���
}WEB_URL ;

typedef struct {
	unsigned int cmd_numb; 
	char *cmd_str;
}AT_CMD_LIST ;

typedef struct {
	char phone[UNICODE_PHONE_LEN];	  //�绰�����UNICODE����
	char sm[UNICODE_SM_LEN];	  //�������UNICODE����
}ST_MSG ;

AT_CMD_LIST AT_list[] = {
							{N_AT_CR_LF,			AT_CR_LF},				//"AT\r\n"
							{N_AT_SetTxtMod,		AT_SetTxtMod},			//"AT+CMGF=1\r\n"	//�����ı�ģʽ
							{N_AT_SetGSMCharSet,	AT_SetGSMCharSet},		//"AT+CSCS=\"GSM\"\r\n"	//����GSM�ַ���
							{N_AT_SetSMSHint,		AT_SetSMSHint},			//"AT+CNMI=2,1\r\n"			//��������Ϣ��ʾ
							{N_AT_SetUCS2CharSet,	AT_SetUCS2CharSet},		//"AT+CSCS=\"UCS2\"\r\n"		//����UCS2�ַ���
							{N_AT_SetSMSModPara,	AT_SetSMSModPara},		//"AT+CSMP=17,167,2,25\r\n"	//�����ı�ģʽ����
							{N_AT_DelSMSTstCmd,		AT_DelSMSTstCmd},		//"AT+CMGD=?\r\n"			//����֧�ֵ�ɾ������Ϣ��������
							{N_AT_DelSMS,			AT_DelSMS},				//"AT+CMGD=40,2\r\n"			//�������40������Ϣ
							{N_RT_RING,				RT_RING},				//����֪ͨ
							{N_AT_ReadSMS,			AT_ReadSMS},			//"AT+CMGR="					//��ȡ��**������
							{N_AT_SndPhone,			AT_SndPhone},			//"AT+CMGS="					//���Ͷ���	�����˵绰����

							{N_RT_SM_WaitRd,		RT_SM_WaitRd},			//"+CMTI:\"SM\""				//�����ж��ŵ���ģ��
							{N_RT_SM_ARRIVE_UNREAD,	RT_SM_ARRIVE_UNREAD},			//"+CMGR:" ���ŵ������ʼ��ʾ +CMGR:���Ƿ��Ѷ��������绰���롱������������������
							{N_RT_SM_ARRIVE_READ,	RT_SM_ARRIVE_READ},			//"+CMGR:" ���ŵ������ʼ��ʾ +CMGR:���Ƿ��Ѷ��������绰���롱������������������
							{N_RT_SM_PRE_UNREAD,	RT_SM_PRE_UNREAD},			//
//							{N_AT_CheckFeePhone,	AT_CheckFeePhone},			//ͨ��10086��ѯ�绰�� ���
							{N_RT_SndPrompt,		RT_SndPrompt},			//ͨ��10086��ѯ�绰�� ���
							   
							{N_RT_POWER_OFF,		RT_POWER_OFF},			//"NORMAL POWER DOWN\r\n"		//GSM �ػ�
							{N_I_DontKnow,			RT_I_DontKnow}
							 };


struct SND_FIFO {
	u8 		pointer;
	char 	phone[CMD_Q_MAX][UNICODE_PHONE_LEN];
	char	sm[CMD_Q_MAX][UNICODE_SM_LEN];
} snd_queue;

struct RD_FIFO {
	u8 		pointer;
	char 	index[SIM_Q_MAX][3];
} rd_queue;

//-----------------------
u8 enc_send_size = 10;       //��Ҫ���͵��ֽ���
u8 enc_send_buf[256] = {0};		//������������ֽ�256
                                                                   //http://standards.ieee.org/develop/regauth/oui/public.html     Search for:00-11-22
unsigned char  mymac[6] ={0x00, 0x11, 0x22, 0x33, 0x44, 0x55};     //0x00 0x11 0x22= CIMSYS Inc  MAC�̶����̺�, 0x33,0x44,0x55ʹ��STM32��*Ψһ*ID����ó�

/***********************************************/
// home net
//unsigned char  myip[4] 	= {192, 168, 1, 123};
//unsigned char  mysm[4] 	= {255, 255, 255, 0};
//unsigned char  mygw[4] 	= {192, 168, 1, 1};
//u8 RemoteIP[4] 			= {192, 168, 1, 104};


// office net
//unsigned char  myip[4] 	= {192, 168, 41, 250};
//unsigned char  mysm[4] 	= {255, 255, 0, 0};
//unsigned char  mygw[4] 	= {192, 100, 106,248};
//u8 RemoteIP[4] 		 	= {192, 168, 41, 82};
//unsigned char	DNServer[4] 	= {192,100,106,12}; //DNS server
/***********************************************/


			//��������վ���Ի�ȡ����IP��ַ

//---------webclient para------------
bool		 webclient_data_flag = FALSE;
u8			 webclient_data[BUF1_LEN];
u16 volatile webclient_data_len	= 0 ;

extern void		resolv_reset(void);
//by david
//---------webclient para------------
//---------EEPROM------------

//u16 VirtAddVarTab[NumbOfVar] = {0x5555, 0x6666, 0x7777};
extern u16 EE_Init(void);
extern u16 EE_ReadVariable(u16 VirtAddress, u16* Data);
extern u16 EE_WriteVariable(u16 VirtAddress, u16 Data);

#define 	NET_CMD_SHOW_MEM_PARA		"show mem para"
#define 	NET_CMD_SHOW_FLASH_PARA		"show flash para"
#define 	NET_CMD_SHOW_ACT_WEB		"show active web"

#define		NET_CMD_SAVE_MEM_TO_FLASH	"save mem to flash"  
#define		NET_CMD_READ_FLASH_TO_MEM	"read flash to mem"  
#define		NET_CMD_COMP_FALSH			"compare flash with mem"  
#define 	NET_CMD_get					"getflash:"
#define		NET_CMD_set					"setflash:"  
#define 	NET_CMD_NONE				"�޴�����\r\n"

#define 	NET_CMD_HELP0				"help\x09\x09\x09����\r\n"
#define 	NET_CMD_HELP1				"show mem para\x09\x09��ʾ��ǰ���в���\r\n"
#define 	NET_CMD_HELP2				"show flash para\x09\x09��ʾflash����\r\n"
#define 	NET_CMD_HELP3				"show active web\x09\x09��ʾ��ǰ����web����\r\n"
#define 	NET_CMD_HELP4				"save mem to flash\x09�洢��ǰ���в�����flash\r\n"
#define 	NET_CMD_HELP5				"read flash to mem\x09��flash�������ڴ�\r\n"
#define 	NET_CMD_HELP6				"compare flash with mem\x09�Ƚ�flash����ǰ����\r\n"

#define 	NET_CMD_HELP7				"getflash:para_name\x09\x09��ȡĳ�������ǰֵ\r\n"
#define 	NET_CMD_HELP8				"setflash:para_name=******\x09����ĳ�����\r\n"
#define 	NET_CMD_HELP9				"para_name\x09\x09�����������£�\r\n"


#define 	STATUS_CONFIG	0
#define 	STATUS_RUN		1


typedef struct {
	u8				vaddr;					//�����������ַ��Flash�洢��ģ��EEPROM
	const 	 char 	nm[PARA_L_CMD_EN];		//��������
	const	 char	cn[PARA_L_CMD_CN];    //���������������ڰ���
	unsigned char 	ip[PARA_L_IP];		//ip��ַ
} IP_PARA_SET ;
typedef struct {
	u8				vaddr;					//�����������ַ��Flash�洢��ģ��EEPROM
	const    char 	nm[PARA_L_CMD_EN];		//��������
	const	 char	cn[PARA_L_CMD_CN];    //���������������ڰ���
	char 			tel[PARA_L_PHONE];	//�绰����
} PHONE_PARA_SET ;
typedef struct {
	u8				vaddr;					//�����������ַ��Flash�洢��ģ��EEPROM
	const    char 	nm[PARA_L_CMD_EN];		//��������
	const	 char	cn[PARA_L_CMD_CN];    //���������������ڰ���
	char 			val[PARA_L_WEB];		//web ��ַ���ļ����ơ���ʼ�ؼ��֡������ؼ���
} WEB_PARA_SET ;

typedef struct {
	u8				vaddr;					//�����������ַ��Flash�洢��ģ��EEPROM
	const    char 	nm[PARA_L_CMD_EN];	    //��������
	const	 char	cn[PARA_L_CMD_CN];      //���������������ڰ���
	char	 		val[PARA_L_WEB];        //email ��ַ���û����������
} EMAIL_PARA_SET ;

typedef struct {
	IP_PARA_SET		ips[PARA_ACCOUNT_IP];	 	//IP��ַ������4��
	PHONE_PARA_SET	tels[PARA_ACCOUNT_PHONE];	//�绰���������4�� 	
	WEB_PARA_SET	webs[PARA_ACCOUNT_WEB];		//web������12�� 	
	EMAIL_PARA_SET	emails[PARA_ACCOUNT_EMAIL];	//email������5�� from,to,cc,user,password	
}PARASETS;



PARASETS parasets  = {	 
	//  220 words be saved in virtual EEPROM , 
	//  this number must be matched up with NumbOfVar which is defined in EEPROM.h 
	//  IP��ַ
	{{0,"myip",		"\x09\x09�豸IP",	{192, 168, 41, 250}},				//�������ƣ������ڴ���ʼλ�ã�myip[4]
	{2,"mysm",		"\x09\x09��������",	{255, 255, 255,  0}},				//�������ƣ������ڴ���ʼλ�ã�mysm[4]
	{4,"mygw",		"\x09\x09����IP",	{192, 168, 41, 1}},				//�������ƣ������ڴ���ʼλ�ã�megw[4]
	{6,"dhcpip",	"\x09[DHCP]��IP",	{192, 168, 41, 1}},				//�������ƣ������ڴ���ʼλ�ã�DHCPserverIP[4]
	{8,"remoteip",	"\x09��������IP",	{192, 168, 41, 82}},				//�������ƣ������ڴ���ʼλ�ã�remoteIP[4]
	{10,"dnsip",	"\x09\x09[DNS]��IP",{192, 100, 106,12}}},			//�������ƣ������ڴ���ʼλ�ã�dnsIP[4]

//	{{0,"myip",		"\x09\x09�豸IP",	{192, 168, 1, 250}},				//�������ƣ������ڴ���ʼλ�ã�myip[4]
//	{2,"mysm",		"\x09\x09��������",	{255, 255, 255,0}},				//�������ƣ������ڴ���ʼλ�ã�mysm[4]
//	{4,"mygw",		"\x09\x09����IP",	{192, 168, 1, 2}},				//�������ƣ������ڴ���ʼλ�ã�megw[4]
//	{6,"dhcpip",	"\x09[DHCP]��IP",	{192, 168, 1, 2}},				//�������ƣ������ڴ���ʼλ�ã�DHCPserverIP[4]
//	{8,"remoteip",	"\x09��������IP",	{192, 168, 1, 104}},				//�������ƣ������ڴ���ʼλ�ã�remoteIP[4]
//	{10,"dnsip",	"\x09\x09[DNS]��IP",{192, 168, 1, 2}}},			//�������ƣ������ڴ���ʼλ�ã�dnsIP[4]


	// �绰
	{{12,"superph",	"\x09�绰1",		"13700000000"},				//�������ƣ������ڴ���ʼλ�ã�spphone[14] ,Ҫת����UNICODE�����ʹ��
	{19,"userph1",	"\x09�绰2",		"13800000002"},				//�������ƣ������ڴ���ʼλ�ã�userphone1[14],Ҫת����UNICODE�����ʹ��
	{26,"userph2",	"\x09�绰3",		"13800000003"},				//�������ƣ������ڴ���ʼλ�ã�userphone2[14],Ҫת����UNICODE�����ʹ��
	{33,"svrph",	"\x09\x09��Ӫ�̵绰","10086"}},						//�������ƣ������ڴ���ʼλ�ã�servicephone[14],Ҫת����UNICODE�����ʹ��
	// �ⲿ��վ	1	: http://www.3322.org/dyndns/getip','ip2city.dat',0,NULL	
	{{40,"weburl",	"\x09web��ַ",		"www.3322.org"},					//�������ƣ������ڴ���ʼλ�ã�web1_url[30]
	{60,"webfile",	"\x09web�ļ�",		"/dyndns/getip','ip2city.dat',0,NULL"},						//�������ƣ������ڴ���ʼλ�ã�web1_fn[30]
	{80,"webkws",	"\x09��ʼ�ؼ���",	"f\r\n"},					//�������ƣ������ڴ���ʼλ�ã�web1_kw_S[30]
	{100,"webkwe",	"\x09�����ؼ���",	"\r\n"}},						//�������ƣ������ڴ���ʼλ�ã�web1_kw_E[30]
	// email�ʼ����Ų���
	//Ӧ�ã�   parasets.
	//    :		   emails[0]~emails[4] 	���:�������䡢�������䡢�������䡢�����û����������
	//    ��   parasets.emails[].vaddr	��ŵ�ַ
	//	  ��   parasets.emails[].nm		����Ӣ����
	//    ��   parasets.emails[].cn		����������
	//    :    parasets.emails[].val		����ֵ
	{{120,"emfrom",	"\x09��������",		"aaaaaaaa@163.com"},			//�������ƣ������ڴ���ʼλ�ã�����ֵ
	{140,"emto",	"\x09\x09��������",	"bbbbbbbb@139.com"},			//�������ƣ������ڴ���ʼλ�ã�����ֵ
	{160,"emcc",	"\x09\x09��������",	"cccccccc@21cn.com"},			//�������ƣ������ڴ���ʼλ�ã�����ֵ
	{180,"emuser",	"\x09�����û�", 	"ZGFccccddggg21haWw="},			//�������ƣ������ڴ���ʼλ�ã�����ֵ
	{200,"empw",	"\x09\x09�������",	"cGddfdgQ="}}	//�������ƣ������ڴ���ʼλ�ã�����ֵ
};										 
										 
extern init_virtual_addr(void);

//---------EEPROM------------
//����������������������������������������������������������������������������������������������������������������������������������������������������������������

u8 tcp_server_flag = 0;												//tcp�����������Ͽ��ı�־
unsigned int   myserverport = 4001;
u16 RemotePort = REMOTE_PORT ;  									//Զ�˶˿�

struct uip_conn *my_tcp_conn;  										//tcp�ͻ�������


#define  TCP_KEEPALIVE_TIME			10                             //TCP������ģʽ�¶Կͻ��˵ĳ�ʱ��� Ĭ��60s


//--------------TCP/IP ״̬Ǩ�Ʊ��----------------------------------------------------------------------------------------------------------------------------------------
unsigned char __IO  uip_poll_ack_static  = 0;          //CLINET��SERVER������ͨ��״̬���,�ϵ�Ĭ��ֵΪ0=�ͻ��˴��� �Ͽ����߱��ر���

#define   CLINT_ACKED_CLOSED             0			 //��������Ϊ:�ͻ��˴���,�Ͽ����߱��ر���״̬
#define   CLINT_ACKED_SYNACK             1			 //��������Ϊ:�ͻ��˷���SYN���������ӦSYN+ACK��������ACKED״̬
#define   SERVER_ACTIVE_SEND             2 			 //��������Ϊ:�ͻ����״����ӳɹ���״̬��,����clientû�����ݹ���, ������������ͻ��˷������ݺ�״̬
#define   CLINT_NEWDAT_ACKED_CARRY       3           //��������Ϊ:�ͻ��˷��������ݸ��������󣬷���������NEWDATA״̬,����������PSH+ACKģʽ�����������Ӵ����͵�client
#define   CLINT_ACKED_CARRY              4           //��������Ϊ:�ͻ���ACKED��EWDATAģʽ���Դ��ķ���������(CARRYģʽ������)
#define   CLINT_ACKED_NORMAL             5           //��������Ϊ:һֱ�ڷ�����������->�ͻ���ACKED->������������->�ͻ���ACKEDģʽ  ����ѭ��ģʽ,��δ����NEWDATA״̬�µ��Դ� 
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void Init_Enc28j60_Chip(void);
void loop_process_tcpip(void);
void loop_process_uart1(void);
//void loop_process_uart2(void);
void loop_process_sm(void);
void loop_feed_softdog(void);
void tcp_data_Analyse(void)	;
void uart_data_Analyse( u8 *uart_data);

void Init_uip(void);
void Tcp_Init(void);
void Web_Link_Init(void);

void uip_main(void);
void sys_time_poll(void);
void sys_time_nms(void);
void Get_SerialNum(void);
void getSmtpSvr(char *smtpSvr, char *from);


bool IpStrToU8(char *ipStr, u8 *ipaddr_1_to_4);
void IpU8ToStr(u8 *ip, u16 port, char *ip_port_str) ;
void IpU16ToStr(u16_t *ipaddr, char *ipString );
void AsciiIpPortToUncode(char *ip_port_ascii, char *ip_port_unicode);

//extern u16_t getlastport();


//IP ��ַ��ͬ��ʽת��
//------------------


u16 AsciiToUnsignInt (unsigned char s[]);		 					//ASCII��U8��
void AsciiToUnicode(char *ascii, char *unicode );		//ASCII��UNICODE��

bool IsDot(char c);
bool Isdigit(char c);

char *ParsePageIpAddr(char *serverdata, char *startStr, char *endStr );
void sendIP2phone(char *phone, char* ipaddr);
bool IsValidPhone(char *phone);

void GetActWeb(WEB_URL *ActWeb);
void net_cmd_process(void *rawdata, u16 datalen);
// ------------------------------------------------------------------
//  local port remote ip string 
// ------------------------------------------------------------------
void lport2ripStr(u16_t lport , uip_ipaddr_t ripaddr, u16_t rport ,char *port_ip_str);

void debug_info_show(char *info, u16_t len);
/*! \ Get_SerialNum
 *
 */
void Get_SerialNum(void) 
{ 
	u32 Device_Serial0, Device_Serial1, Device_Serial2;   
	Device_Serial0 = *(vu32*)(0x1FFFF7E8); 
	Device_Serial1 = *(vu32*)(0x1FFFF7EC); 
	Device_Serial2 = *(vu32*)(0x1FFFF7F0);
	mymac[3]=(u8 )(Device_Serial0>>1);
	mymac[4]=(u8 )(Device_Serial1>>2);
	mymac[5]=(u8 )(Device_Serial2>>3);    	   /*MAC���3�ֽ�����STM��ΨһID���㣬�ر�ע��˷������ܴ����ظ�����Ҫ����Ӧ��������������MAC��Ψһ��*/
}


/*! \loop_feed_softdog
 *
 */
void loop_feed_softdog(void)
{
  Sys_Dog_Count=0;			    //ι��
}

//����������������������������������������������������������������������������������������������������������������������������������������������������������������
void feed_GSM_wakeup_softdog(void)
{
  GSM_Heartbeat_Count=0;			    // GSM ��ʱ���ѹ�
}

void feed_Get_IP_softdog(void)
{
  Get_IP_Req_Timer=0;			    		// ι������ʱ��ȡIP��ַ��
}

void feed_GSM_offline_softdog(void)
{
  GSM_offline_counter = 0;			    // GSM ���߱�־ ���
}

//����������������������������������������������������������������������������������������������������������������������������������������������������������������

/*! \brief led flash in a quite mode for a while when power up.
 *
 */
void LedPwrUp(void) {
    u8 s =0;
    for(s=0; s<20; s++) {		//flash in short time when power in
        LED_Green_FLASH();
        delay_ms(30);
    }
}
void LedGreenFlashSlow(void) {
    u8 s =0;
    for(s=0; s<10; s++) {		//flash in receive time UART 
        LED_Green_FLASH();
        delay_ms(30);
    }
}
void LedGreenFlashFast(void) {
    u8 s =0;
    for(s=0; s<20; s++) {		//flash in receive time ETH
        LED_Green_FLASH();
		//LED_Red_FLASH();
        delay_ms(30);
    }

}

//-------------------------------------------------------------------------------
void tcp_data_Analyse()
{
//����������������������������������������������������������������������������������������������������������������������������������������������������������������
//		UART:        
//			rcv_usart1_array[]Ϊ UART ���յ������ݻ�������
//					��󳤶ȣ� BUF1_LEN = 1024��
//		            ʵ�ʳ���:  Rcv_Usart1_To_Array() ���
//			rcv_usart1_data_len :���ڽ��յ������ݳ���
//			USART1_Put_Data(uip_appdata, uip_len)  :  ���ڷ��ͺ�����
//		ETH:
//			uip_appdata:   TCP���͡��������ݻ�������
//			uip_newdata() �������ݵ���ETH���ջ�����
//			uip_send(uip_appdata, uip_len)  : ��̫�����ͺ���
//���������������������������������������������������������������������������������������������������������������������������������������������������������������� 

/*    char   *nptr = "Error Receive Data From Eth .\r\n" ;
	char *tel = "AT\r\n";    
	if (uip_newdata()) {
		if(memcmp( uip_appdata , tel, 5) !=0 ) {
			uip_len = strlen(nptr);
			memcpy(uip_appdata,	nptr, uip_len);
		}
	
	}
*/
//	LedGreenFlashFast();
}

//---------------------------------------------------------------------

//-----�Ӽ�����------
void XEmailAddr(char *email, char *XemailX)
{
	u8	len =0;

	memcpy(XemailX,"<" ,1);
	len ++ ;
	memcpy(XemailX + len ,email ,strlen(email));
	len += strlen(email) ;
	memcpy(XemailX + len ,">" ,1);
	len ++ ;
	
	XemailX[len] = '\0';
}

void	GetEmailUserPW()
{
	memcpy(smtp_user, parasets.emails[3].val, strlen(parasets.emails[3].val));  //����BASE64���û���
	memcpy(smtp_pw,   parasets.emails[4].val, strlen(parasets.emails[4].val));  //����BASE64�Ŀ���
}

//---------------------------------------------
//��DNS���У�Ѱ��IP��ַ������Ҳ�����תѯ��DNS������
//---------------------------------------------
u16_t * LookupIP(char *URL)
{
	uip_ipaddr_t *ipaddr;
  	uip_ipaddr_t addr;
	uip_ipaddr_t dnsipaddr ;//����IP���ͱ���

    //  DNS���ܳ�ʼ��by david 
    resolv_init();
    uip_ipaddr(dnsipaddr, parasets.ips[5].ip[0], parasets.ips[5].ip[1], parasets.ips[5].ip[2], parasets.ips[5].ip[3]);  //DNS server
    resolv_conf(dnsipaddr);

	// DNS���ܳ�ʼ�� ------ ���� ------

    // First check if the host is an IP address.
	 
  	ipaddr = &addr;
  	if(uiplib_ipaddrconv(URL, (unsigned char *)addr) == 0) {	  //���������Ƿ���һ��IP��ַ��0�����ǣ�1����
    	ipaddr = (uip_ipaddr_t *)resolv_lookup(URL);			  //�Ƿ��Ѿ���������������Ѿ�������������IP��ַ�� ipaddr��
    	if(ipaddr != NULL) {	  //����Ѿ��� DNS��������IP��ַ����ִ��������룻
			if(WEBCLIENT_DEBUG)	{	
			    char info[] = " is used."  ;
				char ipString[20] ;
				IpU16ToStr((u16_t *)ipaddr,ipString);

				memcpy(webclient_data ,ipString , strlen(ipString) );
				memcpy(webclient_data + strlen(ipString), info , strlen(info));
				webclient_data_len = strlen(ipString) + strlen(info);	
				webclient_data_flag	= TRUE ;		
			}
			return (u16_t *)ipaddr;
		}
		else {	 	//���û�� ��Ч��IP��ַ����ȡ���򾭹�DNS�����ȡIP��ַ
			//DNS���ܳ�ʼ������
			resolv_query(URL);     //���� DNS ��ȡIP��ַ		

			//  ������Ϣ ------------
			if(WEBCLIENT_DEBUG)	{	
				
				memcpy(webclient_data , "DNS lookup...\r\n" , 15);
				memcpy(webclient_data +15, URL , strlen(URL));
				webclient_data_len = 15 + strlen(URL) ;		
				webclient_data_flag	= TRUE ;		
			}
			
			// DNS���ܳ�ʼ������
			return NULL;
		}
  	}
}

void	SendEmail_163(char *subject, char * msg)
{
	//Ӧ�ã�   parasets.
	//    :		   emails[0]~emails[4] 	���:�������䡢�������䡢�������䡢�����û����������
	//    ��   parasets.emails[].vaddr	��ŵ�ַ
	//	  ��   parasets.emails[].nm		����Ӣ����
	//    ��   parasets.emails[].cn		����������
	//    :    parasets.emails[].val		����ֵ

	static char from[PARA_L_WEB],to[PARA_L_WEB],cc[PARA_L_WEB];

	// --- �� Email ��ַǰ���  <> ����
	XEmailAddr(parasets.emails[0].val, from);
	XEmailAddr(parasets.emails[1].val, to);
	XEmailAddr(parasets.emails[2].val, cc);

	//smtp_send(char *to, char *cc, char *from,
	//  char *subject, char *msg, u16_t msglen)

	smtp_send(to, cc, from,	subject, msg, strlen(msg));
	
}


/******************************************************************************
* �������߳�ʼ��
* λ��  ӡˢ��·��P2  9/10��, CPU  PB12 ��
*        ʹ�����߶̽Ӻ󣬴�������̬�����������ã�����������Ϣ�洢��FLASH�У�
* 		 ����ȥ����������̬�����������FLASH�����ò�����
*******************************************************************************/
void	IO_Config()
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	// Configure the system clocks 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	// Configure the GPIO ports
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		     		//��������
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		     //��������

    GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/******************************************************************************
* ���Ե�ǰ���Ӵ�������̬������̬
* Return    : - STATUS_CONFIG��	����̬��0��
*             - STATUS_RUN��	����̬��1��
*******************************************************************************/
u8	now_status()
{
	return  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12);
}

/******************************************************************************
* write ip para to EEPROM
* Return    : - Success or error status:
*             - FLASH_COMPLETE: on success,
*             - PAGE_FULL: if valid page is full
*             - NO_VALID_PAGE: if no valid page was found
*             - Flash error code: on write Flash error
*******************************************************************************/

u16 save_para_IP(IP_PARA_SET *ip_para)
{
	//�����ַ�һ���洢�ռ� ��EEPROM����ռ��ǰ���16λһ�������ַ�洢��
	u16	status1,status2 ;

	status1 = EE_WriteVariable(ip_para->vaddr,   ((ip_para->ip[0])<<8 | (ip_para->ip[1])));
	status2 = EE_WriteVariable(ip_para->vaddr+1, ((ip_para->ip[2])<<8 | (ip_para->ip[3])));

	if(status1 != FLASH_COMPLETE)
		return status1;
	return status2;
}
//------------------------------------------
// read ip para from EEPROM
//------------------------------------------
void read_para_IP(IP_PARA_SET *ip_para)
{
	//�����ַ�һ���洢�ռ� ��EEPROM����ռ��ǰ���16λһ�������ַ�洢��
	u16	data;	

	EE_ReadVariable(ip_para->vaddr, &data);
	ip_para->ip[0] =  data >> 8 ;
	ip_para->ip[1] =  data & 0x00ff ;

	EE_ReadVariable(ip_para->vaddr+1, &data);
	ip_para->ip[2] =  data >> 8 ;
	ip_para->ip[3] =  data & 0x00ff ;

}

u16 save_para_phone(PHONE_PARA_SET *phone_para)
{
	int i=0 ;
	u16	status;
	for( i=0; i<PARA_L_PHONE/2 ; i++)  {//�����ַ�һ���洢�ռ� ��EEPROM����ռ��ǰ���16λһ�������ַ�洢��
		status = EE_WriteVariable(phone_para->vaddr+i,   ((phone_para->tel[2*i])<<8 | (phone_para->tel[2*i+1])));
		if(	status != FLASH_COMPLETE)
			return status;
	}
	return status;
}

void read_para_phone(PHONE_PARA_SET *phone_para)
{
	u16	data;	
	int i=0;
	for( i=0; i<PARA_L_PHONE/2 ; i++) { //�����ַ�һ���洢�ռ� ��EEPROM����ռ��ǰ���16λһ�������ַ�洢��
		EE_ReadVariable(phone_para->vaddr+i, &data);
		phone_para->tel[2*i] 		=  data >> 8 ;
		phone_para->tel[2*i+1] 	=  data & 0x00ff ;
	}
	
}

u16 save_para_URL(WEB_PARA_SET *web_para)
{
	int i=0;
	u16 status;
	for( i=0; i<PARA_L_WEB/2 ; i++) {	 //�����ַ�һ���洢�ռ� ��EEPROM����ռ��ǰ���16λһ�������ַ�洢��
		status = EE_WriteVariable(web_para->vaddr+i,   ((web_para->val[2*i])<<8 | (web_para->val[2*i+1])));
		if(	status != FLASH_COMPLETE)
			return status;
	}
	return status;
}
void read_para_URL(WEB_PARA_SET *web_para)
{
	u16	data;	
	int i=0;
	for( i=0; i<PARA_L_WEB/2 ; i++) { //�����ַ�һ���洢�ռ� ��EEPROM����ռ��ǰ���16λһ�������ַ�洢��
		EE_ReadVariable(web_para->vaddr+i, &data);
		web_para->val[2*i] 		=  data >> 8 ;
		web_para->val[2*i+1] 	=  data & 0x00ff ;
	}
}

u16 save_para_email(EMAIL_PARA_SET *email_para)
{
	int i=0;
	u16 status;
	for( i=0; i<PARA_L_WEB/2 ; i++) {	 //�����ַ�һ���洢�ռ� ��EEPROM����ռ��ǰ���16λһ�������ַ�洢��
		status = EE_WriteVariable(email_para->vaddr+i,   ((email_para->val[2*i])<<8 | (email_para->val[2*i+1])));
		if(	status != FLASH_COMPLETE)
			return status;
	}
	return status;
}
void read_para_email(EMAIL_PARA_SET *email_para)
{
	u16	data;	
	int i=0;
	for( i=0; i<PARA_L_WEB/2 ; i++) { //�����ַ�һ���洢�ռ� ��EEPROM����ռ��ǰ���16λһ�������ַ�洢��
		EE_ReadVariable(email_para->vaddr+i, &data);
		email_para->val[2*i] 	=  data >> 8 ;
		email_para->val[2*i+1] 	=  data & 0x00ff ;
	}
}


//------------------------------------------

void	save_mem_to_flash()
{
	int i=0;
	u16 len ;
	u16 	write_status;

	if (now_status() != STATUS_CONFIG) {
		char info[] = "Config switch is not in config status,set is unsuccessful !";
		debug_info_show(info,strlen(info));
		return;
	}


	//--- save IP para ------------
	for(i=0;i<PARA_ACCOUNT_IP ; i++)  {//��IP ��������Ѱ�� 
		write_status = save_para_IP(parasets.ips+i) ;
		if(write_status != FLASH_COMPLETE) {
			char info[] = "IP save set is ERR !";
			debug_info_show(info,strlen(info));
			return;
		}
	}
	//--- save phone  para ------------
	for(i=0;i<PARA_ACCOUNT_PHONE ; i++) {
		len = strlen(parasets.tels[i].tel);
		//flash �洢�����ֶ��뷽ʽ�����Բ��롣
		if( len%2 ==0) {
			parasets.tels[i].tel[len] 	= '\0';
			parasets.tels[i].tel[len+1] = '\0';
		}						
		
		write_status = save_para_phone(parasets.tels+i) ;
		if(write_status != FLASH_COMPLETE) {
			char info[] = "phone save set is ERR !";
			debug_info_show(info,strlen(info));
			return;
		}
	}
	//--- save web para ------------
	for(i=0;i<PARA_ACCOUNT_WEB ; i++) {
		len = strlen(parasets.webs[i].val);
		//flash �洢�����ֶ��뷽ʽ�����Բ��롣
		if( len%2 ==0) {
			parasets.webs[i].val[len] 	= '\0';
			parasets.webs[i].val[len+1] = '\0';
		}						

		write_status = save_para_URL(parasets.webs+i) ;
		if(write_status != FLASH_COMPLETE) {
			char info[] = "web para save set is ERR !";
			debug_info_show(info,strlen(info));
			return;
		}
	}

	//--- save email para ------------
	for(i=0;i<PARA_ACCOUNT_EMAIL ; i++) {
		len = strlen(parasets.emails[i].val);
		//flash �洢�����ֶ��뷽ʽ�����Բ��롣
		if( len%2 ==0) {
			parasets.emails[i].val[len] 	= '\0';
			parasets.emails[i].val[len+1] = '\0';
		}						

		write_status = save_para_email(parasets.emails+i) ;
		if(write_status != FLASH_COMPLETE) {
			char info[] = "email para save set is ERR !";
			debug_info_show(info,strlen(info));
			return;
		}
	}


	{
		char info[] = "para set is OK !";
		debug_info_show(info,strlen(info));
	}
}
//------------------------------------------
void ShowActiveWeb() 
{
	WEB_URL ActWebStr ;
	GetActWeb(&ActWebStr);  //���õ�ǰ�����web

	webclient_data_len = 0 ;

	memcpy(webclient_data + webclient_data_len, ActWebStr.URL , strlen(ActWebStr.URL)) ; 
	webclient_data_len += strlen(ActWebStr.URL);	
	memcpy(webclient_data + webclient_data_len, "\r\n" , 2) ; 
	webclient_data_len += 2;	

	memcpy(webclient_data + webclient_data_len, ActWebStr.file , strlen(ActWebStr.file)) ; 
	webclient_data_len += strlen(ActWebStr.file);	
	memcpy(webclient_data + webclient_data_len, "\r\n" , 2) ; 
	webclient_data_len += 2;	

	memcpy(webclient_data + webclient_data_len, ActWebStr.s_str , strlen(ActWebStr.s_str)) ; 
	webclient_data_len += strlen(ActWebStr.s_str);	
	memcpy(webclient_data + webclient_data_len, "\r\n" , 2) ; 
	webclient_data_len += 2;	

	memcpy(webclient_data + webclient_data_len, ActWebStr.e_str , strlen(ActWebStr.e_str)) ; 
	webclient_data_len += strlen(ActWebStr.e_str);	
	memcpy(webclient_data + webclient_data_len, "\r\n" , 2) ; 
	webclient_data_len += 2;	

	webclient_data_flag	= TRUE ;

}

void GetActWeb(WEB_URL *WebStr)
{
	memcpy(WebStr->URL, 	parasets.webs[0].val, PARA_L_WEB);
	memcpy(WebStr->file,	parasets.webs[1].val, PARA_L_WEB);
	memcpy(WebStr->s_str, 	parasets.webs[2].val, PARA_L_WEB);
	memcpy(WebStr->e_str, 	parasets.webs[3].val, PARA_L_WEB);
}

void	read_flash_to_mem()
{
	int i=0;

	for(i=0; i<PARA_ACCOUNT_IP ; i++) 
		read_para_IP(parasets.ips+i) ;
		
	for(i=0; i<PARA_ACCOUNT_PHONE ; i++) 
		read_para_phone(parasets.tels+i) ;
		
	for(i=0; i<PARA_ACCOUNT_WEB ; i++) 
		read_para_URL(parasets.webs+i) ;

	for(i=0; i<PARA_ACCOUNT_EMAIL ; i++) 
		read_para_email(parasets.emails+i) ;
}

//-----------------------------------------
// �Ƚϵ�ǰ�ڴ����еĲ�����flash �洢�Ĳ���
//-----------------------------------------
void	CompareFlashWithMem()
{
		int i=0 ,j=0;
		u16 len = 0 ;
		u16	err = 0;

		char ip_ascii[10];

		IP_PARA_SET 		ip ;
		PHONE_PARA_SET 		tel;
		WEB_PARA_SET 		web_str;
		EMAIL_PARA_SET 		email_str;

		webclient_data_len = 0 ;
		for(i=0; i<PARA_ACCOUNT_IP ; i++)  {
			err = 0;
			//��ʾ��������
			len = strlen(parasets.ips[i].nm);
			memcpy(webclient_data + webclient_data_len, parasets.ips[i].nm, len);
			webclient_data_len += len;
			memcpy(webclient_data + webclient_data_len, "=", 1);
			webclient_data_len ++;

			//��ȡflash�洢�Ĳ���ֵ
			ip.vaddr = parasets.ips[i].vaddr ;
			read_para_IP(&ip);

			//��ʾ����ֵ
			for(j=0; j<PARA_L_IP ; j++)  {
				if(ip.ip[j] != parasets.ips[i].ip[j]) {
					err++;
					//flash������ʾ
					memcpy(webclient_data + webclient_data_len, "flash:", 6);
					webclient_data_len +=6;
					//flash����
					itoa(ip.ip[j],ip_ascii,10) ;
					memcpy(webclient_data + webclient_data_len,ip_ascii , strlen(ip_ascii)) ; 
					webclient_data_len += strlen(ip_ascii);

					memcpy(webclient_data + webclient_data_len, "    " , 4) ; 
					webclient_data_len += 4;
					//�ڴ������ʾ
					memcpy(webclient_data + webclient_data_len, "mem:", 4);
					webclient_data_len +=4;
					//�ڴ����
					itoa(parasets.ips[i].ip[j],ip_ascii,10) ;
					memcpy(webclient_data + webclient_data_len,ip_ascii , strlen(ip_ascii)) ; 
					webclient_data_len += strlen(ip_ascii);

					memcpy(webclient_data + webclient_data_len, "\r\n" , 2) ; 
					webclient_data_len += 2;
				}
			}
			if(err !=0 ) {
				memcpy(webclient_data + webclient_data_len, "ERR\r\n" , 5) ; 
				webclient_data_len += 5;	
			}
			else {
				memcpy(webclient_data + webclient_data_len, "OK\r\n" , 4) ; 
				webclient_data_len += 4;	
			}
		}

		
		for(i=0; i<PARA_ACCOUNT_PHONE ; i++)  {
			//��ʾ��������
			len = strlen(parasets.tels[i].nm);
			memcpy(webclient_data + webclient_data_len, parasets.tels[i].nm, len);
			webclient_data_len += len;
			memcpy(webclient_data + webclient_data_len, ":", 1);
			webclient_data_len ++;

			//��ȡflash�洢�Ĳ��� ֵ
			tel.vaddr = parasets.tels[i].vaddr ;
			read_para_phone(&tel);


			//��ʾ����ֵ
			if(strlen(tel.tel) == strlen(parasets.tels[i].tel) && 
			    memcmp(tel.tel, parasets.tels[i].tel , strlen(parasets.tels[i].tel))==0) { 
				memcpy(webclient_data + webclient_data_len, "flash=mem\r\n" , 11) ; 
				webclient_data_len += 11;	
			}
			else {
				memcpy(webclient_data + webclient_data_len, "flash != mem\r\n" , 14) ; 
				webclient_data_len += 14;	
			}
		}

		for(i=0; i<PARA_ACCOUNT_WEB ; i++)  {
			//��ʾ��������
			len = strlen(parasets.webs[i].nm);
			memcpy(webclient_data + webclient_data_len, parasets.webs[i].nm, len);
			webclient_data_len += len;
			memcpy(webclient_data + webclient_data_len, ":", 1);
			webclient_data_len ++;

			//��ȡflash�洢�Ĳ��� ֵ
			web_str.vaddr = parasets.webs[i].vaddr ;
			read_para_URL(&web_str);

			//��ʾ����ֵ
			// �Ƚ� flash �� memery ֵ
			if(strlen(web_str.val) == strlen(parasets.webs[i].val)) {

				for(j=0; j<strlen(parasets.webs[i].val) ; j++) {
					if( web_str.val[j] != parasets.webs[i].val[j])
						break;
				}
				if(j>=strlen(parasets.webs[i].val)) {

				//if(memcmp(web_str.val, parasets.webs[i].val , strlen(parasets.webs[i].val))!=0) { 
					memcpy(webclient_data + webclient_data_len, "flash=mem\r\n" , 11) ; 
					webclient_data_len += 11;	
				}
				else {
					char num[10];

					itoa(j, num, 10);
					memcpy(webclient_data + webclient_data_len, "flash str ", 10 );
					webclient_data_len += 10;	

					memcpy(webclient_data + webclient_data_len, num , strlen(num)) ; 
					webclient_data_len += strlen(num);	
					
					memcpy(webclient_data + webclient_data_len, "!= mem str \r\n", 13) ;
					webclient_data_len += 13;	
				}
			}
			else {
				memcpy(webclient_data + webclient_data_len, "str len != mem\r\n" , 16) ; 
				webclient_data_len += 16;	
			}
		}

		for(i=0; i<PARA_ACCOUNT_EMAIL ; i++)  {
			//��ʾ��������
			len = strlen(parasets.emails[i].nm);
			memcpy(webclient_data + webclient_data_len, parasets.emails[i].nm, len);
			webclient_data_len += len;
			memcpy(webclient_data + webclient_data_len, ":", 1);
			webclient_data_len ++;

			//��ȡflash�洢�Ĳ��� ֵ
			email_str.vaddr = parasets.emails[i].vaddr ;
			read_para_email(&email_str);

			//��ʾ����ֵ
			// �Ƚ� flash �� memery ֵ
			if(strlen(email_str.val) == strlen(parasets.emails[i].val)) {

				for(j=0; j<strlen(parasets.emails[i].val) ; j++) {
					if( email_str.val[j] != parasets.emails[i].val[j])
						break;
				}
				if(j>=strlen(parasets.emails[i].val)) {

				//if(memcmp(web_str.val, parasets.webs[i].val , strlen(parasets.webs[i].val))!=0) { 
					memcpy(webclient_data + webclient_data_len, "flash=mem\r\n" , 11) ; 
					webclient_data_len += 11;	
				}
				else {
					char num[10];

					itoa(j, num, 10);
					memcpy(webclient_data + webclient_data_len, "flash str ", 10 );
					webclient_data_len += 10;	

					memcpy(webclient_data + webclient_data_len, num , strlen(num)) ; 
					webclient_data_len += strlen(num);	
					
					memcpy(webclient_data + webclient_data_len, "!= mem str \r\n", 13) ;
					webclient_data_len += 13;	
				}
			}
			else {
				memcpy(webclient_data + webclient_data_len, "str len != mem\r\n" , 16) ; 
				webclient_data_len += 16;	
			}
		}
		
		webclient_data_flag	= TRUE ;
}

//-----------------------------------------
// ��ʾ��ǰflash �洢�Ĳ���
//-----------------------------------------
void	show_flash_para()
{

		int i=0 ,j=0;
		u16 len = 0;
		char ip_ascii[10];

		IP_PARA_SET 		ip ;
		PHONE_PARA_SET 		tel;
		WEB_PARA_SET 		web_str;
		EMAIL_PARA_SET 		email_str;

		webclient_data_len = 0 ;
		for(i=0; i<PARA_ACCOUNT_IP ; i++)  {
			//��ʾ��������
			len = strlen(parasets.ips[i].nm);
			memcpy(webclient_data + webclient_data_len, parasets.ips[i].nm, len);
			webclient_data_len += len;
			memcpy(webclient_data + webclient_data_len, "=", 1);
			webclient_data_len ++;

			//��ȡflash�洢�Ĳ���ֵ
			ip.vaddr = parasets.ips[i].vaddr ;
			read_para_IP(&ip);

			//��ʾ����ֵ
			for(j=0; j<PARA_L_IP ; j++)  {
				itoa(ip.ip[j],ip_ascii,10) ;
				memcpy(webclient_data + webclient_data_len,ip_ascii , strlen(ip_ascii)) ; 
				webclient_data_len += strlen(ip_ascii);

				memcpy(webclient_data + webclient_data_len,"." , 1) ; 
				webclient_data_len ++;
			}
			memcpy(webclient_data + webclient_data_len, "\r\n" , 2) ; 
			webclient_data_len += 2;
		}

		
		for(i=0; i<PARA_ACCOUNT_PHONE ; i++)  {
			//��ʾ��������
			len = strlen(parasets.tels[i].nm);
			memcpy(webclient_data + webclient_data_len, parasets.tels[i].nm, len);
			webclient_data_len += len;
			memcpy(webclient_data + webclient_data_len, "=", 1);
			webclient_data_len ++;

			//��ȡflash�洢�Ĳ��� ֵ
			tel.vaddr = parasets.tels[i].vaddr ;
			read_para_phone(&tel);

			//��ʾ����ֵ
			len	= (PARA_L_PHONE>strlen(tel.tel))? strlen(tel.tel):PARA_L_PHONE;
			memcpy(webclient_data + webclient_data_len, tel.tel , len) ; 
			webclient_data_len += len;

			memcpy(webclient_data + webclient_data_len, "\r\n" , 2) ; 
			webclient_data_len += 2;
		}

		for(i=0; i<PARA_ACCOUNT_WEB ; i++)  {
			//��ʾ��������
			len = strlen(parasets.webs[i].nm);
			memcpy(webclient_data + webclient_data_len, parasets.webs[i].nm, len);
			webclient_data_len += len;
			memcpy(webclient_data + webclient_data_len, "=", 1);
			webclient_data_len ++;

			//��ȡflash�洢�Ĳ��� ֵ
			web_str.vaddr = parasets.webs[i].vaddr ;
			read_para_URL(&web_str);

			//��ʾ����ֵ
			len	= (PARA_L_WEB>strlen(web_str.val))? strlen(web_str.val):PARA_L_WEB;
			memcpy(webclient_data + webclient_data_len, web_str.val , len) ; 
			webclient_data_len += len;

			memcpy(webclient_data + webclient_data_len, "\r\n" , 2) ; 
			webclient_data_len += 2;
		}

		for(i=0; i<PARA_ACCOUNT_EMAIL ; i++)  {
			//��ʾ��������
			len = strlen(parasets.emails[i].nm);
			memcpy(webclient_data + webclient_data_len, parasets.emails[i].nm, len);
			webclient_data_len += len;
			memcpy(webclient_data + webclient_data_len, "=", 1);
			webclient_data_len ++;

			//��ȡflash�洢�Ĳ��� ֵ
			email_str.vaddr = parasets.emails[i].vaddr ;
			read_para_email(&email_str);

			//��ʾ����ֵ
			len	= (PARA_L_WEB>strlen(email_str.val))? strlen(email_str.val):PARA_L_WEB;
			memcpy(webclient_data + webclient_data_len, email_str.val , len) ; 
			webclient_data_len += len;

			memcpy(webclient_data + webclient_data_len, "\r\n" , 2) ; 
			webclient_data_len += 2;
		}

		webclient_data_flag	= TRUE ;

}
void	show_mem_para()
{
		int i=0 ,j=0;
		u16 len = 0;
		char ip_ascii[10];

		webclient_data_len = 0 ;
		for(i=0; i<PARA_ACCOUNT_IP ; i++)  {
			//��ʾ��������
			len = strlen(parasets.ips[i].nm);
			memcpy(webclient_data + webclient_data_len, parasets.ips[i].nm, len);
			webclient_data_len += len;
			memcpy(webclient_data + webclient_data_len, "=", 1);
			webclient_data_len ++;

			//��ʾ���� ֵ
			for(j=0; j<PARA_L_IP ; j++)  {
				itoa(parasets.ips[i].ip[j],ip_ascii,10) ;
				memcpy(webclient_data + webclient_data_len,ip_ascii , strlen(ip_ascii)) ; 
				webclient_data_len += strlen(ip_ascii);

				memcpy(webclient_data + webclient_data_len,"." , 1) ; 
				webclient_data_len ++;
			}
			memcpy(webclient_data + webclient_data_len, "\r\n" , 2) ; 
			webclient_data_len += 2;
		}

		
		for(i=0; i<PARA_ACCOUNT_PHONE ; i++)  {
			//��ʾ��������
			len = strlen(parasets.tels[i].nm);
			memcpy(webclient_data + webclient_data_len, parasets.tels[i].nm, len);
			webclient_data_len += len;
			memcpy(webclient_data + webclient_data_len, "=", 1);
			webclient_data_len ++;

			//��ʾ���� ֵ
			len	= (PARA_L_PHONE>strlen(parasets.tels[i].tel))? strlen(parasets.tels[i].tel):PARA_L_PHONE;
			memcpy(webclient_data + webclient_data_len, parasets.tels[i].tel , len) ; 
			webclient_data_len += len;

			memcpy(webclient_data + webclient_data_len, "\r\n" , 2) ; 
			webclient_data_len += 2;
		}

		for(i=0; i<PARA_ACCOUNT_WEB ; i++)  {
			//��ʾ��������
			len = strlen(parasets.webs[i].nm);
			memcpy(webclient_data + webclient_data_len, parasets.webs[i].nm, len);
			webclient_data_len += len;
			memcpy(webclient_data + webclient_data_len, "=", 1);
			webclient_data_len ++;

			//��ʾ���� ֵ
			len	= (PARA_L_WEB>strlen(parasets.webs[i].val))? strlen(parasets.webs[i].val):PARA_L_WEB;
			memcpy(webclient_data + webclient_data_len, parasets.webs[i].val , len) ; 
			webclient_data_len += len;

			memcpy(webclient_data + webclient_data_len, "\r\n" , 2) ; 
			webclient_data_len += 2;
		}

		for(i=0; i<PARA_ACCOUNT_EMAIL ; i++)  {
			//��ʾ��������
			len = strlen(parasets.emails[i].nm);
			memcpy(webclient_data + webclient_data_len, parasets.emails[i].nm, len);
			webclient_data_len += len;
			memcpy(webclient_data + webclient_data_len, "=", 1);
			webclient_data_len ++;

			//��ʾ���� ֵ
			len	= (PARA_L_WEB>strlen(parasets.emails[i].val))? strlen(parasets.emails[i].val):PARA_L_WEB;
			memcpy(webclient_data + webclient_data_len, parasets.emails[i].val , len) ; 
			webclient_data_len += len;

			memcpy(webclient_data + webclient_data_len, "\r\n" , 2) ; 
			webclient_data_len += 2;
		}

		webclient_data_flag	= TRUE ;

}
void ShowMemTelUnicode()
{
	char tmp[400];
	u16	len = 0 ;

	memcpy(	tmp+ len, phonelist.t1 , strlen(phonelist.t1));
	len +=strlen(phonelist.t1);
	memcpy(	tmp+ len, "\r\n" , 2);
	len +=2;

	memcpy(	tmp+ len, phonelist.t2 , strlen(phonelist.t2));
	len +=strlen(phonelist.t2);
	memcpy(	tmp+ len, "\r\n" , 2);
	len +=2;

	memcpy(	tmp+ len, phonelist.t3 , strlen(phonelist.t3));
	len +=strlen(phonelist.t3);
	memcpy(	tmp+ len, "\r\n" , 2);
	len +=2;

	memcpy(	tmp+ len, phonelist.svr , strlen(phonelist.svr));
	len +=strlen(phonelist.svr);
	memcpy(	tmp+ len, "\r\n" , 2);
	len +=2;
	
	debug_info_show( tmp, len);


}
TelAsciiToUnicode(char *TelAscii, char *TelUnicode)
{

	u8	len;
	char tmp_tel[PARA_L_PHONE+6];
	
	len	= (PARA_L_PHONE>strlen(TelAscii))? strlen(TelAscii):PARA_L_PHONE;

	if(TelAscii[0] == '+') {  //����� +86 �Ͳ������ӣ����ں�߶�������ĵ绰�Ƚ�
		memcpy(tmp_tel ,TelAscii, len);
		tmp_tel[len] = '\0';
	}
	else {
		memcpy(tmp_tel,"+86",3); //���û�� +86 ������
		memcpy(tmp_tel + 3 ,TelAscii, len);
		tmp_tel[len+3] = '\0';
	}

	AsciiToUnicode(tmp_tel, TelUnicode );

}
void TelLoad()
{
	TelAsciiToUnicode(parasets.tels[0].tel, phonelist.t1);
	TelAsciiToUnicode(parasets.tels[1].tel, phonelist.t2);
	TelAsciiToUnicode(parasets.tels[2].tel, phonelist.t3);
	TelAsciiToUnicode(parasets.tels[3].tel, phonelist.svr);
}

//-------------------------------------
//������
//		��flash�洢�����ò��������ڴ�
//		��flash�洢��ASCII�绰����ת��ΪUNICODE�ĵ绰����
//-------------------------------------
void	ReadConfigPara()
{
	if (now_status() ==  STATUS_RUN) {
		char info[]= "��ǰ:<����̬><Running Status>" ;
		read_flash_to_mem();	//��flash���õ��ڴ�
		debug_info_show(info,strlen(info));
	}
	else {
		char info[]= "��ǰ:<����̬><Configing Status>" ;
		debug_info_show(info,strlen(info));
	}
	//�ѵ绰����ת����UNICODE��ʽ����GSMģ��ʹ��
	TelLoad();			//�绰����ת���� UNICODE
}	 



void	init_sm_queue()
{

	//��ʼ��������ķ��Ͷ���
	snd_queue.pointer = 0 ;

	//��ʼ��������Ķ����Ŷ���
	rd_queue.pointer = 0;
	//for(i=0; i< SIM_Q_MAX; i++) {
	//  	rd_queue.index[i] = 1;
	//}

}
//------------------------------------
bool s_FIFO_Null()
{
	return ((snd_queue.pointer == 0)?TRUE:FALSE) ;
}

bool  s_FIFO_Full()
{
	return ((snd_queue.pointer == CMD_Q_MAX)?TRUE:FALSE) ;
}
bool  r_FIFO_Null()				//�ж϶����Ŷ����Ƿ�Ϊ��
{
	return (rd_queue.pointer == 0)?TRUE:FALSE;
}
bool  r_FIFO_Full()			   //�ж϶����Ŷ����Ƿ� �Ѿ���
{
	return ((rd_queue.pointer == SIM_Q_MAX)?TRUE:FALSE) ;
}
//-------------------------------------------
bool s_FIFO_head(ST_MSG *msg)
{
	if(! s_FIFO_Null()) {	 //���в���

		memcpy(msg->phone,	snd_queue.phone[0] ,strlen(snd_queue.phone[0])) ;
		msg->phone[strlen(snd_queue.phone[0])] = '\0';		

		memcpy(msg->sm, 	snd_queue.sm[0] ,	strlen(snd_queue.sm[0])) ;
		msg->sm[strlen(snd_queue.sm[0])] = '\0';		

		return TRUE;
	}
	else
		return FALSE;

}
bool s_FIFO_pop(ST_MSG *msg)
{
	int i;

	if( ! s_FIFO_Null()) {	 //���в���

		memcpy(msg->phone,	snd_queue.phone[0] ,strlen(snd_queue.phone[0])) ;
		msg->phone[strlen(snd_queue.phone[0])] = '\0';		

		memcpy(msg->sm,		snd_queue.sm[0] ,	strlen(snd_queue.sm[0])) ;
		msg->sm[strlen(snd_queue.sm[0])]= '\0';
		
		for(i=1; i< snd_queue.pointer ; i++) {
			memcpy(snd_queue.phone[i-1],	snd_queue.phone[i] ,strlen(snd_queue.phone[i])) ;
			snd_queue.phone[i-1][strlen(snd_queue.phone[i])]= '\0';

			memcpy(snd_queue.sm[i-1],		snd_queue.sm[i] ,	strlen(snd_queue.sm[i])) ;
			snd_queue.sm[i-1][strlen(snd_queue.sm[i])]= '\0';

		}

		snd_queue.pointer-- ;

		return TRUE;
	}
	else
		return FALSE ;  	//���пգ�ֱ���˳�
	
}
bool s_FIFO_push(ST_MSG *msg)
{
	if(	s_FIFO_Full()) 	  //������
		return FALSE;
	else {							  //���в���

		memcpy(snd_queue.phone[snd_queue.pointer],	msg->phone ,strlen(msg->phone)) ;
		snd_queue.phone[snd_queue.pointer][strlen(msg->phone)]= '\0';

		memcpy(snd_queue.sm[snd_queue.pointer],	msg->sm ,strlen(msg->sm)) ;
		snd_queue.sm[snd_queue.pointer][strlen(msg->sm)]= '\0';

		snd_queue.pointer++ ;
  
		return TRUE;
	}
}
bool s_FIFO_head_modify(ST_MSG *msg)
{

	if( ! s_FIFO_Null()) {	 //���в���

		memcpy(snd_queue.phone[0],	msg->phone ,strlen(msg->phone)) ;
		snd_queue.phone[0][strlen(msg->phone)]= '\0';

		memcpy(snd_queue.sm[0],	msg->sm ,strlen(msg->sm)) ;
		snd_queue.sm[0][strlen(msg->sm)]= '\0';
	
		return TRUE;
	}
	else
		return FALSE ;  	//���пգ�ֱ���˳�
}
bool r_FIFO_head(char *sn_str)
{
	if( ! r_FIFO_Null()) {	 //���в���
		sn_str[0] = rd_queue.index[0][0];
		sn_str[1] = rd_queue.index[0][1];
		sn_str[2] = '\0';
		return TRUE;
	}
	else
		return FALSE;		
}
bool r_FIFO_pop(char *sn_str)
{
	int i;

	if( ! r_FIFO_Null() ) {	 //���в���

		sn_str[0] = rd_queue.index[0][0];
		sn_str[1] = rd_queue.index[0][1];
		sn_str[2] = '\0';

		for(i=1; i<SIM_Q_MAX; i++) {
			rd_queue.index[i-1][0] = rd_queue.index[i][0];
			rd_queue.index[i-1][1] = rd_queue.index[i][1];
			rd_queue.index[i-1][2] = rd_queue.index[i][2];
		}

		rd_queue.pointer-- ;

		return TRUE;
	}
	else

		return FALSE ;

}
bool r_FIFO_push(char *sn_str)
{
	if(	r_FIFO_Full() ) 	  //������
		return FALSE;
	else {							  //���в���
		rd_queue.index[rd_queue.pointer][0] = sn_str[0];
		rd_queue.index[rd_queue.pointer][1] = sn_str[1];
		rd_queue.index[rd_queue.pointer][2] = sn_str[2];

		rd_queue.pointer++ ;

		return TRUE;
	}
}
//-------------------------------------------------------------------------
void clear_rcv_buf()
{
	int i ; 
	u8 rcv_clean[BUF1_LEN];
	
	for(i=0; i<BUF1_LEN ; i++) 
		if( rcv_usart1_array[i] != '\r' &&  rcv_usart1_array[i] != '\n' )
			break;
	rcv_usart1_data_len = rcv_usart1_data_len - i ;
	memcpy( rcv_clean, rcv_usart1_array+i , rcv_usart1_data_len ) ;
	memcpy( rcv_usart1_array , rcv_clean,   rcv_usart1_data_len ) ;
}

void wait_GSM_active()
{
	//---------------------------------------------------------------------
	//  �ϵ��ʼ���������׶Σ�
	//	��һ�׶Σ�   �ȴ��ϵ��������Ҫ�ȴ�GSMģ�鷵��������Ϣ��
	//		#define UART_READY0			"RDY\r\n"
	//		#define UART_READY1			"+CFUN: 1\r\n"
	//		#define UART_READY2			"+CPIN: READY\r\n"
	//		#define UART_READY3			"Call Ready\r\n"
	//		#define UART_READY4			"AT\r\n\r\nOK\r\n"
	//---------------------------------------------------------------------

	clear_rcv_buf();

	if( rcv_usart1_data_len < 6)	//���������ָ���������
		return;
	
	//������뷢��״̬ʱ��Ҫ�˳�
	if(memcmp(rcv_usart1_array , "AT\r\n\r\n>" , 7) ==0 ) { 
		snd_usart1_data_len  = 1;
		snd_usart1_array[0] = 0x1A ;
		USART1_Put_Data(snd_usart1_array, snd_usart1_data_len);
		Uart1SndDataFlag = 1; 	
		return;
	}

	if(memcmp(rcv_usart1_array , RT_RING , strlen(RT_RING)) ==0 ) { 
		snd_usart1_data_len  = strlen(ATH);
		memcpy(snd_usart1_array , ATH , snd_usart1_data_len);
		USART1_Put_Data(snd_usart1_array, snd_usart1_data_len);
		Uart1SndDataFlag = 1; 	
		return;
	}
	//----------------------------------------------------
	//���������ҪĿ�ģ�
	//�� "AT+CMGS="	�����֮�󣬽��뷢��״̬��> "�����ǳ��ַ�����Ϣ�����GSMģ���޷��˳��˴���Ĺ���״̬��
	//ͨ���˶δ��룬�˳��˴���״̬����������ѭ����ȡ���ŵ�����״̬��
	if(memcmp(rcv_usart1_array + rcv_usart1_data_len - strlen(SND_STATUS) , SND_STATUS , strlen(SND_STATUS)) ==0 ) {
		snd_usart1_data_len  = 1;
		snd_usart1_array[0] = SMS_END_CHAR;
		USART1_Put_Data(snd_usart1_array, 1);
		Uart1SndDataFlag = 1; 	
		return;
	}
	//------������������֮һ ˵���ܹ�����  ��ʼ��������--------
	if((memcmp((rcv_usart1_array + rcv_usart1_data_len- strlen(UART_READY2)), UART_READY2 , strlen(UART_READY2))==0) ||
	   (memcmp((rcv_usart1_array + rcv_usart1_data_len- strlen(UART_READY3)), UART_READY3 , strlen(UART_READY3))==0) ||
	   (memcmp((rcv_usart1_array + rcv_usart1_data_len- strlen(UART_READY4)), UART_READY4 , strlen(UART_READY4))==0) ) {

		GSM_active_flag = 1 ;		// GSM �ܹ���������󣬲��ٱ��δ��룻
		snd_usart1_data_len  = strlen("GSM_Active_OK\r\n");
		memcpy(snd_usart1_array , "GSM_Active_OK\r\n", snd_usart1_data_len);
		Uart1SndDataFlag = 1; 	// �ѷ��͵����ڵ���Ϣ ��ETH �ַ��ͳ�ȥ�����ԡ�

	}

}
void init_GSM()
{
	//---------------------------------------------------------------------
	//	�ڶ��׶Σ�  ���Խ��� AT��������ζ�GSMģ���ʼ��
	//---------------------------------------------------------------------
	// AT_CR_LF					"AT\r\n"					//����ͬ����������
	// AT_SetTxtMod				"AT+CMGF=1\r\n"				//�����ı�ģʽ
	// AT_SetGSMCharSet			"AT+CSCS=\"GSM\"\r\n"		//����GSM�ַ���  Ӣ�Ķ���
	// AT_SetSMSHint			"AT+CNMI=2,1\r\n"			//��������Ϣ��ʾ
	// 1.�����ʼ�������Ȳ��ҽ��յ��Ĵ��Ƿ��ͳ�ȥ������
	// 2.����Ҳ�����i == 250 ; Ӧ�÷���ATͬ��������Խ׶���ʱ ���� I Dont Know 
	// 3.����ҵ���
	//		1)��������������,������ء�OK������������
	//		2)������ء�ERROR�� �ط����
	//---------------------------------------------------------------------
	
	int i =0;
	
	clear_rcv_buf();

	// GSM���壬ֱ�ӹһ�
	if(memcmp(rcv_usart1_array , RT_RING , strlen(RT_RING)) ==0 ) { 
		snd_usart1_data_len  = strlen(ATH);
		memcpy(snd_usart1_array , ATH , snd_usart1_data_len);
		USART1_Put_Data(snd_usart1_array, snd_usart1_data_len);
		Uart1SndDataFlag = 1; 	
		return;
	}
	if(memcmp(rcv_usart1_array , RT_POWER_OFF , strlen(RT_POWER_OFF)) ==0 ) { 
		GSM_active_flag = 0 ;	//�����־��Ϊ 0
		init_GSM_end_flag = 0 ; //��ʼ����־��Ϊ 0
		snd_usart1_data_len  = strlen("Power off 2..\r\n");
		memcpy(snd_usart1_array , "Power off 2 ..\r\n" , snd_usart1_data_len);
		Uart1SndDataFlag = 1; 	// �ѷ��͵����ڵ���Ϣ ��ETH �ַ��ͳ�ȥ�����ԡ�
		return;
	}
	//----------------------------------------------------
	//���������ҪĿ�ģ�
	//�� "AT+CMGS="	�����֮�󣬽��뷢��״̬��> "�����ǳ��ַ�����Ϣ�����GSMģ���޷��˳��˴���Ĺ���״̬��
	//ͨ���˶δ��룬�˳��˴���״̬����������ѭ����ȡ���ŵ�����״̬��
	if(memcmp(rcv_usart1_array + rcv_usart1_data_len - strlen(SND_STATUS) , SND_STATUS , strlen(SND_STATUS)) ==0 ) {
		snd_usart1_data_len  = 1;
		snd_usart1_array[0] = SMS_END_CHAR;
		USART1_Put_Data(snd_usart1_array, 1);
		Uart1SndDataFlag = 1; 	
		return;
	}

	for(i=0 ;i< sizeof(AT_list) / sizeof(AT_CMD_LIST); i++){
		if((memcmp(rcv_usart1_array , AT_list[i].cmd_str ,strlen(AT_list[i].cmd_str))==0 ) &&
		   (memcmp(rcv_usart1_array + strlen(AT_list[i].cmd_str) , "\r\nOK\r\n",6 )==0 )) 		   //���ء�OK�� ��Ӧ
				break;
	}

	if(i < (sizeof(AT_list) / sizeof(AT_CMD_LIST)))  { 	
 		switch(AT_list[i].cmd_numb) {   // ���ص�ֵ  �� ���͵�ֵ ��ͬ����OK��־����
			case N_AT_CR_LF:			// �����ǣӣ͡�ͬ����ɣ��������ı�ģʽ�� "AT+CMGF=1\r\n"				
				snd_usart1_data_len  = strlen(AT_SetTxtMod);					
				memcpy(snd_usart1_array , AT_SetTxtMod, snd_usart1_data_len);
				USART1_Put_Data(snd_usart1_array, snd_usart1_data_len);			
				break;
			case N_AT_SetTxtMod :		// ��������ı�ģʽ�ɹ��� "AT+CMGF=1\r\n"	������GSM�ַ�����
				if(GSM_ONLY_R_W_EN_SM == 1 ) {		// ֻ��дӢ�Ķ���
					snd_usart1_data_len  = strlen(AT_SetGSMCharSet);		// AT_SetGSMCharSet			"AT+CSCS=\"GSM\"\r\n"	
					memcpy(snd_usart1_array , AT_SetGSMCharSet, snd_usart1_data_len);
					USART1_Put_Data(snd_usart1_array, snd_usart1_data_len);
				}
				else {							   // ��д��Ӣ�Ķ��� �������ַ��� UCS2
					snd_usart1_data_len  = strlen(AT_SetUCS2CharSet);		// AT_SetGSMCharSet			"AT+CSCS=\"GSM\"\r\n"	
					memcpy(snd_usart1_array , AT_SetUCS2CharSet, snd_usart1_data_len);
					USART1_Put_Data(snd_usart1_array, snd_usart1_data_len);
				}
				break;
			case N_AT_SetUCS2CharSet :		// �������UCS2 �ַ��� �ɹ������� �ı�������//"AT+CSMP=17,167,2,25\r\n"	//�����ı�ģʽ����
				snd_usart1_data_len  = strlen(AT_SetSMSModPara);		// 
				memcpy(snd_usart1_array , AT_SetSMSModPara, snd_usart1_data_len);
				USART1_Put_Data(snd_usart1_array, snd_usart1_data_len);
				break;

			case N_AT_SetSMSModPara:	  //�����ı������ɹ�  
			case N_AT_SetGSMCharSet :	 //��������ַ����ɹ��������� ģ���ڽ��յ���Ϣʱ����֪ͨ��"AT+CNMI=2,1\r\n"			
				snd_usart1_data_len  = strlen(AT_SetSMSHint);
				memcpy(snd_usart1_array , AT_SetSMSHint, snd_usart1_data_len);
				USART1_Put_Data(snd_usart1_array, snd_usart1_data_len);
				break;

			case N_AT_SetSMSHint :		//��� ��������Ϣ��ʾ �ɹ������ʼ�����
				
				init_GSM_end_flag = 1; 		//�������������������� ��λ��ʼ������ ���� ��־��������������������

				snd_usart1_data_len  = strlen("GSM_Init_OK\r\n");
				memcpy(snd_usart1_array , "GSM_Init_OK\r\n", snd_usart1_data_len);

				break;
		}
	
		Uart1SndDataFlag = 1; 	// �ѷ��͵����ڵ���Ϣ ��ETH �ַ��ͳ�ȥ�����ԡ�
	}
}
void catch_phone_sm(u8* rcv_msg, char* phone, char* smtxt)
{
	// ���յ����ŵĸ�ʽ��
	//+CMGR: "REC UNREAD","002B0038003600310033003700300032003900340038003900320034","536B","14/07/05,13:10:42+32"
	//\r\n
	//00440074
	//\r\n
	//---------��ȡ�绰����----------
	//+CMGR: "REC UNREAD","002B0038003600310033003700300032003900340038003900320034","536B","14/07/05,13:10:42+32"
	//-----------------------------------------------------------------------------","----------------------------
	int i,j;

	for(i=0;i< BUF1_LEN ;i++) 
	   if(memcmp(rcv_msg + i, 			"\",\"" , 3)== 0 )  
		   break;
	
	for(j=0;j< UNICODE_PHONE_LEN ;j++) 
	   if(memcmp(rcv_msg + i + 3 + j, 	"\",\"" , 3)== 0 )  
		   break;
		
	memcpy(phone , rcv_msg + i + 3 , j );	   //���յ��Ķ��Ŵ洢�����Ժ����
	phone[j] = '\0';

	//---------��ȡ��������---------
	for(i=0;i< BUF1_LEN ;i++) {
	   if(memcmp(rcv_msg + i  ,"\r\n",2)==0) 	//�ʼ�� \r\n 
		   break;
	}
	for(j=0;j< BUF1_LEN ; j++) {
	   if(memcmp(rcv_msg + i + 2 + j  ,"\r\n",2)==0) 
		   break;
	}

	if(j>UNICODE_SM_LEN) 
		j = UNICODE_SM_LEN-1;

	memcpy(smtxt , rcv_msg + i + 2 , j );	   //���յ��Ķ��Ŵ洢�����Ժ����
	smtxt[j] = '\0';
}

void analyse_GSM_SM()
{
	//---------------------------------------------------------------------
	// AT_DelSMSTstCmd,			"AT+CMGD=?\r\n"			//����֧�ֵ�ɾ������Ϣ��������
	// AT_DelSMS,				"AT+CMGD=40,2\r\n"			//�������40������Ϣ
	// RT_SM_WaitRd,			"+CMTI:\"SM\""				//�����ж��ŵ���ģ��
	// RT_SM_ARRIVE,			"+CMGR:" ���ŵ������ʼ��ʾ +CMGR:���Ƿ��Ѷ��������绰���롱������������������
	// 1.�����ʼ�������Ȳ��ҽ��յ��Ĵ��Ƿ��ͳ�ȥ������
	// 2.����Ҳ�����i == 250 ; Ӧ�÷���ATͬ��������Խ׶���ʱ ���� I Dont Know 
	// 3.����ҵ���
	//		1)��������������,������ء�OK������������
	//		2)������ء�ERROR�� �ط����
	//---------------------------------------------------------------------
	
	int i =0 ;	
	u16 volatile snd_SM_text_len			= 8;

	char 		SM_cim_addr[3] ;
	ST_MSG    	msg; 

	char    snd_SM_text[BUF1_LEN];
	char	user_phone[UNICODE_PHONE_LEN] ;



	clear_rcv_buf();
	// GSM���壬ֱ�ӹһ�
	if(memcmp(rcv_usart1_array , RT_RING , strlen(RT_RING)) ==0 ) { 
		snd_usart1_data_len  = strlen(ATH);
		memcpy(snd_usart1_array , ATH , snd_usart1_data_len);
		USART1_Put_Data(snd_usart1_array, snd_usart1_data_len);
		Uart1SndDataFlag = 1; 	
		return;
	}
	if(memcmp(rcv_usart1_array , RT_POWER_OFF , strlen(RT_POWER_OFF)) ==0 ) { 
		GSM_active_flag = 0 ;	//�����־��Ϊ 0
		init_GSM_end_flag = 0 ; //��ʼ����־��Ϊ 0

		snd_usart1_data_len  = strlen("Power off 3..\r\n");
		memcpy(snd_usart1_array , "Power off 3 ..\r\n" , snd_usart1_data_len);
		Uart1SndDataFlag = 1; 	// �ѷ��͵����ڵ���Ϣ ��ETH �ַ��ͳ�ȥ�����ԡ�
	}
	//--------------------------------------------------------------------
	//			USART1_Put_Data(rcv_usart1_array, 13);
	//			Uart1SndDataFlag = 1;
	//--------------------------------------------------------------------

	for(i=0 ;i< sizeof(AT_list) / sizeof(AT_CMD_LIST); i++)
		if(memcmp(rcv_usart1_array , AT_list[i].cmd_str ,strlen(AT_list[i].cmd_str))==0 ) 
				break;
		
	if(i < (sizeof(AT_list) / sizeof(AT_CMD_LIST))) {  	// �ڽ��������� ����Ч���ݣ�Ѱ�ҵ����û��ƥ��ķ���ֵ
 		switch(AT_list[i].cmd_numb) {
			case N_AT_CR_LF:
			case N_AT_SetTxtMod :		//AT_SetTxtMod				"AT+CMGF=1\r\n"				//�����ı�ģʽ
			case N_AT_SetGSMCharSet :	 //AT_SetGSMCharSet			"AT+CSCS=\"GSM\"\r\n"		//����GSM�ַ���
			case N_AT_SetSMSHint :		//AT_SetSMSHint				"AT+CNMI=2,1\r\n"			//��������Ϣ��ʾ
			case N_AT_DelSMS :			//ɾ������Ϣ
					break;

			case N_RT_SM_WaitRd:		
						// +CMTI:"SM",nn\r\n		 strlen(+CMTI:"SM",)=11  
						// 0123456789012 3 4 
						//�������� ,������в��������Ͷ�ȡ������
						
						if(rcv_usart1_array[strlen(RT_SM_WaitRd)+1] == '\r')  {	//��λ���Ĵ洢�ص�
							SM_cim_addr[0]= '0' ;
							SM_cim_addr[1]= rcv_usart1_array[strlen(RT_SM_WaitRd)] ;
						}
						else {
							SM_cim_addr[0]= rcv_usart1_array[strlen(RT_SM_WaitRd)] ;
							SM_cim_addr[1]= rcv_usart1_array[strlen(RT_SM_WaitRd)+1];
						}
						SM_cim_addr[2]= '\0';

						/*
						if(	! r_FIFO_Full()) {	  //���в���
							r_FIFO_push(SM_cim_addr) ;
						}
						*/

						//ֱ�ӷ��Ͷ�ȡ���-----------------------
						snd_usart1_data_len  = strlen(AT_ReadSMS);			
						memcpy(snd_usart1_array , AT_ReadSMS, snd_usart1_data_len);

						memcpy(snd_usart1_array + snd_usart1_data_len, SM_cim_addr, strlen(SM_cim_addr));
						snd_usart1_data_len += strlen(SM_cim_addr);

						snd_usart1_array[snd_usart1_data_len  ]	= '\r';
						snd_usart1_array[snd_usart1_data_len+1]	= '\n';

						snd_usart1_data_len+=2;
						USART1_Put_Data(snd_usart1_array, snd_usart1_data_len);
						Uart1SndDataFlag = 1; 	// �ѷ��͵����ڵ���Ϣ ��ETH �ַ��ͳ�ȥ�����ԡ�
						//-----------------------------------------

					break;
			case N_RT_SM_PRE_UNREAD:		//+CMGL: 
					if(memcmp(rcv_usart1_array + strlen(RT_SM_PRE_UNREAD) , "03" , 2 )==0 ) {
						snd_usart1_data_len  = strlen("OverFlow..");
						memcpy(snd_usart1_array , "OverFlow.." , snd_usart1_data_len);

						//snd_usart1_data_len  = strlen(AT_DelSMS);
						//memcpy(snd_usart1_array , AT_DelSMS, snd_usart1_data_len);
						//USART1_Put_Data(snd_usart1_array, snd_usart1_data_len);
						Uart1SndDataFlag = 1; 	// �ѷ��͵����ڵ���Ϣ ��ETH �ַ��ͳ�ȥ�����ԡ�
					}
					break;


			case N_RT_POWER_OFF:	 	 	//���//"NORMAL POWER DOWN\r\n"		GSM �ػ�, ���¿�ʼ�ȴ�����
					GSM_active_flag = 0 ;	//�����־��Ϊ 0
					init_GSM_end_flag = 0 ; //��ʼ����־��Ϊ 0
					break;

			case N_RT_RING:	 	 	//���//"NORMAL POWER DOWN\r\n"		GSM �ػ�, ���¿�ʼ�ȴ�����
					snd_usart1_data_len  = strlen(ATH);
					memcpy(snd_usart1_array , ATH , snd_usart1_data_len);
					USART1_Put_Data(snd_usart1_array, snd_usart1_data_len);
					Uart1SndDataFlag = 1; 	

					break;
			case N_AT_ReadSMS :			//������Ϣ	 AT_ReadSMS		"AT+CMGR="	//��ȡ��**������
					
					//���������ҪĿ�ģ� ��ֹ�ڷ���״̬�³��ִ���ʱgsmģ������
					//�� "AT+CMGS="	�����֮�󣬽��뷢��״̬��> "�����ǳ��ַ�����Ϣ�����GSMģ���޷��˳��˴���Ĺ���״̬��
					//ͨ���˶δ��룬�˳��˴���״̬����������ѭ����ȡ���ŵ�����״̬��
					if(memcmp(rcv_usart1_array + rcv_usart1_data_len - strlen(SND_STATUS) , SND_STATUS , strlen(SND_STATUS)) ==0 ) {
						snd_usart1_data_len  = 1;
						snd_usart1_array[0] = SMS_END_CHAR;
						USART1_Put_Data(snd_usart1_array, snd_usart1_data_len);
						Uart1SndDataFlag = 1; 	
					}
					break; 

			case N_RT_SndPrompt :	
					break; 

			case N_AT_SndPhone :	// AT_SndPhone   "AT+CMGS="		
					
					/*************************************************
					*�ҵ������д�����ĵ�һ���ڶ����е����
					*i<CMD_Q_MAX ���ҵ��ˣ� i���ǵ�һ�����ڵ����
					*i=CMD_Q_MAX ��û���ҵ�
					*i ������ = 0
					*************************************************/
					
					if( ! s_FIFO_Null() ) {	 //���в���
						s_FIFO_pop(&msg);			 //ȡ����ͷ����Ϣ��Ӧ�Ķ������ݷ���

						snd_SM_text_len = strlen(msg.sm);          //�ҵ�Ҫ���͵Ķ��ų���
						memcpy(snd_SM_text , msg.sm , snd_SM_text_len);	  //���Ƶ���������
						snd_SM_text[snd_SM_text_len]= SMS_END_CHAR;
						snd_SM_text_len++;			   //��ӷ��ͽ����ַ�
						USART1_Put_Data((u8*)snd_SM_text, snd_SM_text_len);			   //ͨ�����ڷ��ͳ�ȥ

						//�ڷ���AT+CMGS����󣬵�����ʾû������ʾʱ���Ͷ���Ϣ�����������´�����ͨ��ETH��ʾ�����͵�����
						if(Uart1SndDataFlag == 0) {
							memcpy(snd_usart1_array , snd_SM_text , snd_SM_text_len);	  //���Ƶ���������
							snd_usart1_data_len = snd_SM_text_len;
						}
						else {
							memcpy(snd_usart1_array+snd_usart1_data_len , snd_SM_text , snd_SM_text_len);	  //���Ƶ���������
							snd_usart1_data_len+=snd_SM_text_len;
						}
						
						
						Uart1SndDataFlag = 1 ; 	//Ҫ��ETH��ʾ������

					} 
					break; 

			case N_RT_SM_ARRIVE_UNREAD:		// RT_SM_ARRIVE_UNREAD		+CMGR: "REC UNREAD" Ҳ����  
					
					catch_phone_sm(rcv_usart1_array,user_phone,snd_SM_text);
					memcpy(msg.phone,user_phone, strlen(user_phone));
					memcpy(msg.sm,   snd_SM_text, strlen(snd_SM_text));

					msg.phone[strlen(user_phone)] = '\0';
					msg.sm[strlen(snd_SM_text)] = '\0';

					//debug_info_show(msg.phone,strlen(msg.phone));
					//��������̬ʱ�������κε绰
					
					if (now_status() == STATUS_CONFIG) {

						if(	! s_FIFO_Full()) 	 //���Ͷ��в�����ѹ��
							s_FIFO_push(&msg) ;

					}
					//��������̬ʱ��ֻ����ָ���ĵ绰��Ϣ�������ָ�����룬��Ѷ��Ų�����д�����====================
					//��ǰ׺ +86 ���ϻ� �ڼ����պ���ʱ�ܹ�ȥ��+86���бȽ�
					else if((memcmp(user_phone , phonelist.t1, strlen(phonelist.t1))==0) ||		//��Ȩ�Ŀ��Է��ʵĵ绰1���绰����ת����UNICODE��
					   	    (memcmp(user_phone , phonelist.t2, strlen(phonelist.t2))==0) ||		//��Ȩ�Ŀ��Է��ʵĵ绰2
					   	    (memcmp(user_phone , phonelist.t3, strlen(phonelist.t3))==0) ||	//��Ȩ�Ŀ��Է��ʵĵ绰3
					   	    (memcmp(user_phone , phonelist.svr, strlen(phonelist.svr))==0 )) {	
						

							if(	! s_FIFO_Full()) 	 //���Ͷ��в�����ѹ��
								s_FIFO_push(&msg) ;
							
					}
					break;

			case N_RT_SM_ARRIVE_READ:			// "+CMGR:" +CMGR:���Ƿ��Ѷ��������绰���롱������������������

					//�����Ķ��ţ�ɾ���Ѷ��ѷ�����
					snd_usart1_data_len  = strlen(AT_DelSMS);		// "AT+CMGD=40,2\r\n"					 
					memcpy(snd_usart1_array , AT_DelSMS , snd_usart1_data_len);
					USART1_Put_Data(snd_usart1_array, snd_usart1_data_len);

					Uart1SndDataFlag = 1; 	// �ѷ��͵����ڵ���Ϣ ��ETH �ַ��ͳ�ȥ�����ԡ�
					break;

			default:
					//snd_usart1_data_len  = strlen(UART_RETURN_ERR);
					//memcpy(snd_usart1_array , UART_RETURN_ERR , snd_usart1_data_len);

					//Uart1SndDataFlag = 1; 	// �ѷ��͵����ڵ���Ϣ ��ETH �ַ��ͳ�ȥ�����ԡ�
					break;
		}
	}
}

//-------------------------------------------------------------------------------

/*! \brief the application main.c
 *
 */
int main(void)
{
	unsigned char i;
	Sys_Dog_start=0;
    led_red_sel = 1;

	Get_SerialNum();//ȡMAC*Ψһ*ֵ
    Platform_Init();
	
	if(CPU_DEBUG) USART1_Put_String("[system info]:/******************************************************* \r\n");
	if(CPU_DEBUG) USART1_Put_String("\r\n");
	ReplaceStr(fw_version,"~VvEeRrSsIiOoNn~",Vxy);	
	if(CPU_DEBUG) USART1_Put_String((unsigned char *)fw_version);
	if(CPU_DEBUG) USART1_Put_String("[system info]:Platform_Init()= OK \r\n");
    LedPwrUp();
	if(CPU_DEBUG) USART1_Put_String("[system info]:LedPwrUp()= OK \r\n");
	SPI_Enc28j60_Init();
	if(CPU_DEBUG) USART1_Put_String("[system info]:SPI_Enc28j60_Init()= OK \r\n");
	Init_Enc28j60_Chip();
	if(CPU_DEBUG) USART1_Put_String("[system info]:Init_Enc28j60_Chip()= OK \r\n");
	if(CPU_DEBUG) USART1_Put_String("[system info]:Enc28j60_EREVID = ");
	if(CPU_DEBUG) Hex2HexStr(enc28j60getrev());
    if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
	if(CPU_DEBUG) USART1_Put_String(" (B1=02,B4=04,B5=05,B7=06) \r\n");

	//������ֻ��������main()���ù�һ�Ρ�����
	// ��ʼ�� ��������
    IO_Config();
	// Unlock the Flash Program Erase controller 
	FLASH_Unlock();
	//-------------------------------
  	// virtual addr Init 
	init_virtual_addr();
	//-------------------------------
  	// EEPROM Init 
  	EE_Init();
	//-------------------------------
	ReadConfigPara();
	//-------------------------------
	Init_uip();
	if(CPU_DEBUG) USART1_Put_String("[system info]:Init_uip()= OK \r\n");
	
	//������������������������

	if(CPU_DEBUG) USART1_Put_String("[system info]:->");
    if(CPU_DEBUG)
	{
		for(i = 0; i < 10; i++)
	   	{
	     	Hex2HexStr(9 - i);
	     	if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
		 	if(CPU_DEBUG) USART1_Put_String("->");
	     	delay_ms(200);
	   	}
	}
	if(CPU_DEBUG) USART1_Put_String("\r\n");
	Sys_Dog_start = 1;
	if(CPU_DEBUG) USART1_Put_String("[system info]:Sys_Dog_start  = OK \r\n");
	if(CPU_DOG) IWDG_Configuration(781); /*5s*/
	if(CPU_DEBUG) USART1_Put_String("[system info]:IWDG_Configuration = OK \r\n");
	if(CPU_DEBUG) USART1_Put_String("[system info]:System Running = OK \r\n");
#ifdef UIP_STATIC_IP_ADDR 
	{
	  	if(CPU_DEBUG) USART1_Put_String("[system info]::) \r\n");
	  	if(CPU_DEBUG) USART1_Put_String("[system info]:********************************************************/ \r\n");
	}
#endif


	init_sm_queue();

    while(1)
    {
		loop_feed_softdog();
		loop_process_tcpip();
		loop_process_uart1();
		loop_process_sm();

//		loop_process_uart2(); 
    }	
}
/*****************************************************
   ����������ַ�����ʽ��ת����UNCODE���GSM���ͳ�ȥ
*****************************************************/
void AsciiToUnicode(char *ascii, char *unicode )
{
	int i=0;
	while(1) {
		if(ascii[i]== '\0' || i > UNICODE_SM_LEN/2-2 ) {
			unicode[i*4] = '\0';
			break;   //300��������
		}
		
		unicode[i*4  ] = '0';
		unicode[i*4+1] = '0';
		
		if( ascii[i] >= '0' && ascii[i] <= '9') {
			unicode[i*4+2] = 0x33; 		//3
			unicode[i*4+3] = ascii[i]; 	//
		}
		else if( ascii[i]== '[') {	//5B
			unicode[i*4+2] = 0x35;	//5
			unicode[i*4+3] = 0x42;	//B
		}
		else if( ascii[i]== ']') {	 //5D
			unicode[i*4+2] = 0x35;	 //5
			unicode[i*4+3] = 0x44;	 //D
		}
		else if( ascii[i]== '.') {	  //2E
			unicode[i*4+2] = 0x32;	  //2
			unicode[i*4+3] = 0x45;	  //E
		}
		else if( ascii[i]== '+') {	  //2B
			unicode[i*4+2] = 0x32;	  //2
			unicode[i*4+3] = 0x42;	  //B
		}
		else if( ascii[i]== ':') {	  //3A
			unicode[i*4+2] = 0x33;	  //3
			unicode[i*4+3] = 0x41;	  //A
		}
		else {					   //���ڴ˷�Χ�����ֺ��ַ� ��ʾΪ��
			unicode[i*4+2] = 0x33;	 //3
			unicode[i*4+3] = 0x46;	 //F
		}
		i++;
	}
}

/*****************************************************
	��10086ת������Ϣ��Ҫ��UNICODE����ת��ΪASCII����
*****************************************************/
void UnicodeToAscii(char *cmd_string)
{
	
	int 	i ;
	char	sm_ASCII[UNICODE_SM_LEN] ;
		
	memset(sm_ASCII ,'\0',UNICODE_SM_LEN); 

	for(i=0; i< strlen(cmd_string); i+=4) 
		memcpy( sm_ASCII+i/2, cmd_string+i+2, 2);
	sm_ASCII[i/2]='\0';

	memcpy(cmd_string,sm_ASCII,i/2); 
	cmd_string[i/2] = '\0';

}

/*****************************************************
* �������������
* �ڴ˺����У������еĵ绰���롢��Ϣ���ݻ�仯
*****************************************************/
void UART_cmd_procese(ST_MSG *cmd)
{

	int i ;
	ST_MSG    msg; 

	char help[UNICODE_SM_LEN];
	int	help_len = 0 ;

	//�����������̬�Ļ��� ����10086�Ķ���	
	if( memcmp(cmd->phone, phonelist.svr, strlen(cmd->phone))==0 ) { 
		
		//�ѷ����̵���Ϣת���� �����û���phonelist.t1
		
		memcpy(msg.phone, 	phonelist.t1, strlen(phonelist.t1));
		memcpy(msg.sm,		cmd->sm, 	 strlen(cmd->sm));

		msg.phone[strlen(phonelist.t1) ] = '\0';
		msg.sm[strlen(cmd->sm)] = '\0';
		
		s_FIFO_head_modify(&msg);

		goto END;
	}
				
	// �������ݷ������Ƿ�Ҫ��ת��	
	if(memcmp(cmd->sm, GSM_CMD_TO , strlen(GSM_CMD_TO))==0) {	 		   //����������Ҫ��ת��������
		//----------------------------------------------------------
		//   ת�������		TO:nnnnnn,ת������
		//	 TO:10086,����
		//	 0054 004F 003A 0031 0030 0030 0038 0036 002C 6D4B 8BD5 
		//	   0   1	2	 3	  4	   5	6	 7	  8	   9	10
		//     T   O	:	  1	   0	0	 8	  6	  ,	   ��   ��
		//		4	 8	 12	  16   20	24   28   32   36	40	44
		//----------------------------------------------------------	
		//�绰������ȡ
								   
		//memcpy(raw_sm ,cmd->sm, UNICODE_SM_LEN);

		for(i=0; i<strlen(cmd->sm); i+=4) 
			if( memcmp((char*)(cmd->sm) + i,"002C",4) ==0) 	//002C ��','�� UNICODE��
				break;

		if(i<UNICODE_SM_LEN ) {


			//��ת����10086�Ķ��Ž����±���ת��
			//�����10086�����������Ҫ��UNICODEת����ASCII����
			memcpy(msg.phone, 	(char *)(cmd->sm) + strlen(GSM_CMD_TO), i-strlen(GSM_CMD_TO));
			memcpy(msg.sm, 		(char *)(cmd->sm) + i + 4, strlen(cmd->sm)-i-4);
			msg.phone[i-strlen(GSM_CMD_TO)] = '\0';			
			msg.sm[strlen(cmd->sm)-i-4] = '\0';			

			if(strcmp(msg.phone,phonelist.svr)==0)  		 
				UnicodeToAscii(msg.sm);

			//memcpy(msg.phone, 	the_phone, strlen(the_phone));
			//memcpy(msg.sm, 	cmd_in_sm, strlen(cmd_in_sm));
	
			s_FIFO_head_modify(&msg);

		}
		goto END;
	}
	if(memcmp(cmd->sm, GSM_CMD_GETIP , strlen(GSM_CMD_GETIP))==0) {	 		   //����������Ҫ��  ��ȡIP��ַ
		
		Web_Link_Init(); 												//������վ����ȡ���������������ձ��ġ����IP��
		
		memcpy(requestIPphone, cmd->phone , strlen(cmd->phone));		//�洢��������� �ֻ�����
		requestIPphone[strlen(cmd->phone)] = '\0';

		memcpy(msg.phone, 	cmd->phone, strlen(cmd->phone));		   //���Żظ��绰���벻��
		memcpy(msg.sm , ACK_WAITING , strlen(ACK_WAITING));			   //�������ݻظ�  ����Ժ�...
		msg.phone[strlen(cmd->phone)] = '\0';			
		msg.sm[strlen(ACK_WAITING)] = '\0' ; 						   //�������ݻظ�  ����Ժ�...

		s_FIFO_head_modify(&msg);
		
		//haveRequestIP = TRUE ;		//  �������ȡIP��  ��־
		//IP_Req_wakeup = 1;			//  ��ʱ����λ��Ϊ���ɹ�����������ʱ��

		goto END;
	}
	if(memcmp(cmd->sm, GSM_CMD_HELP , strlen(GSM_CMD_HELP))==0) {	 		   //����������Ҫ�� ��ð���
		help_len = 0;
		for(i=0; i<HELP_AMOUNT; i++) {								   //��������Ϣ��ϳɶ�������
			memcpy(help + help_len ,ack_help[i],strlen(ack_help[i]));
			help_len += strlen(ack_help[i]);
		}
		
		
		help[help_len] = '\0';

		memcpy(msg.phone, 	cmd->phone, strlen(cmd->phone));		   //���Żظ��绰���벻��
		memcpy(msg.sm , help , help_len+1 );
		msg.phone[strlen(cmd->phone)] = '\0';			


		s_FIFO_head_modify(&msg);

		goto END;
	}
	//��ȡ���� IP��ַ�Ͷ˿ںţ����ó����õ���
	if(memcmp(cmd->sm, GSM_CMD_GETHOST , strlen(GSM_CMD_GETHOST))==0) {	 //����ip��ַ �˿�
		char ip_port_str[30];
		
		memcpy( msg.sm, GSM_INFO_HOST, strlen(GSM_INFO_HOST));

		IpU8ToStr(parasets.ips[4].ip, REMOTE_PORT, ip_port_str);
		AsciiIpPortToUncode(ip_port_str, msg.sm+strlen(GSM_INFO_HOST));

		//---------------------------------
		memcpy(msg.phone, 	cmd->phone, strlen(cmd->phone));		   //���Żظ��绰���벻��
		msg.phone[strlen(cmd->phone)] = '\0';			
		//---------------------------------

		s_FIFO_head_modify(&msg);


		goto END;
	}

	END: 
		return ;
}
/*--------------------------------------------------
* ѭ��������ţ����Ͷ��ţ�
*--------------------------------------------------*/
void loop_process_sm(void)
{
//	int 	sm_queue_sn = 0;   					// ���Ŷ����е����

	static u8 sm_read_cmd_sn   = 1 ; 	  // GSM ����Ϣ��ţ�

	int			len;
	ST_MSG    msg; 
	//char	sim_sm_addr[3];

	//---------------������Ϣ����-----------------------------------
	if(GSM_timing_wakeup == 1){		 //û�ж��ⷢ�͵Ķ���Ϣ����ʱ���ͻ��������GSMģ�� 

		GSM_timing_wakeup = 0;		//�����ʱ��

	
		if( (GSM_active_flag == 0) || (init_GSM_end_flag == 0 )) {	
			snd_usart1_data_len  = strlen(AT_CR_LF);
			memcpy(snd_usart1_array , AT_CR_LF, snd_usart1_data_len);
			goto ENDLPS;
		}
		//-------------------------------------------
		//���� ��������������� ����
		//-------------------------------------------
		/*
		if( ! r_FIFO_Null() ) {	 ////��ȡ���ŵĶ��в��գ�SIM���ж��Ŵ���

			r_FIFO_pop( sim_sm_addr) ;
		//-----------------------------
		
			if(sim_sm_addr[0]==0x30 && sim_sm_addr[1]==0x30 ) {
				snd_usart1_data_len  = strlen("AT_ReadSMS");			
				memcpy(snd_usart1_array , "AT_ReadSMS", snd_usart1_data_len);
  
			goto ENDLPS;
			}
			}
		
		//-----------------------------

			snd_usart1_data_len  = strlen(AT_ReadSMS);			
			memcpy(snd_usart1_array , AT_ReadSMS, snd_usart1_data_len);

			memcpy(snd_usart1_array + snd_usart1_data_len, sim_sm_addr, strlen(sim_sm_addr));
			snd_usart1_data_len += strlen(sim_sm_addr);

			snd_usart1_array[snd_usart1_data_len  ]	= '\r';
			snd_usart1_array[snd_usart1_data_len+1]	= '\n';

			snd_usart1_data_len+=2;
			goto ENDLPS;
		}
		*/
		//-------------------------------------------
		//���淢�� ������� ���������������
		//-------------------------------------------
		if( s_FIFO_Null() == FALSE ) {	 //���Ͷ��в���
			s_FIFO_head(&msg) ;			//��ȡ�����������ǰ���һ��
			UART_cmd_procese(&msg);			//���������������޶����������
			s_FIFO_head(&msg) ;			//��ȡ���µĶ���
			
			//snd_usart1_data_len = strlen("AT_SndPhone");
			//memcpy(snd_usart1_array , "AT_SndPhone", snd_usart1_data_len);

						
			len = strlen(msg.phone) ;
			len = (len< UNICODE_PHONE_LEN) ? len:UNICODE_PHONE_LEN;

			snd_usart1_data_len = strlen(AT_SndPhone);
			memcpy(snd_usart1_array , AT_SndPhone, snd_usart1_data_len);
			memcpy(snd_usart1_array + snd_usart1_data_len , "\"", 1);
			memcpy(snd_usart1_array + snd_usart1_data_len + 1 , msg.phone, len);  	  
			memcpy(snd_usart1_array + snd_usart1_data_len + 1 + len, "\"\r\n", 3);
			snd_usart1_data_len += (1 + len + 3) ;
			
			goto ENDLPS;
		}
		//-------------------------------------------------------------
		// һ����������û���ܹ�������У�Ϊ�˷�ֹ��©�������һ��  ѭ����ȡ ����
		//-------------------------------------------------------------
		{
			snd_usart1_data_len  = strlen(AT_ReadSMS);			
			memcpy(snd_usart1_array , AT_ReadSMS, snd_usart1_data_len);
			snd_usart1_array[snd_usart1_data_len  ]	= 0x30 +  sm_read_cmd_sn/10 ;
			snd_usart1_array[snd_usart1_data_len+1]	= 0x30 +  sm_read_cmd_sn%10 ;
			snd_usart1_array[snd_usart1_data_len+2]	= '\r';
			snd_usart1_array[snd_usart1_data_len+3]	= '\n';
			snd_usart1_data_len+=4;

			sm_read_cmd_sn ++;

			if( sm_read_cmd_sn > SIM_Q_MAX) 						 // ��ȡ�����һ�������ش�ͷ��ʼ�ٶ�
				sm_read_cmd_sn = 1;
		}

		//--------------------------------
		// ��� snd_usart1_array, snd_usart1_data_len ����������ͨ�����ڷ��ͳ�ȥ
		//--------------------------------		

		ENDLPS:
		USART1_Put_Data(snd_usart1_array, snd_usart1_data_len ); 
		Uart1SndDataFlag = 1; 	// �ѷ��͵����ڵ���Ϣ ��ETH ���ͳ�ȥ�����ԡ�
		//--------------------------------
		// ��������û��Ӧ�𣬸�λGSMģ��ĳ�ʼ�׶�
		//--------------------------------		
		GSM_offline_counter ++ ;
		if( GSM_offline_counter == 3 ) {		
			GSM_active_flag 	= 0;
			init_GSM_end_flag 	= 0 ;
			feed_GSM_offline_softdog();
		}
	}

}
/*! \ loop_process_tcpip
 *
 */
void loop_process_tcpip(void)
{
	static unsigned long addlen;

	/*task 1*/
	if(enc28j60_mac_is_linked() == 0)	   /*��ѯ����״̬*/
	{
	    if(((++addlen)%10000) == 0)
	    {
	      	if(CPU_DEBUG) USART1_Put_String("[system info]:enc28j60_mac_is_linked()=:( [RJ45 Disconnect] \r\n");
	    }
	}
	/*task 2*/
	if( (enc28j60Read(EIR) & EIR_TXERIF) )
	{
		if(CPU_DEBUG) USART1_Put_String("[system info]:enc28j60Read(EIR) & EIR_TXERIF=:( [Error->Init_Enc28j60_Chip()] \r\n");
		Init_Enc28j60_Chip();		 //enc28j60оƬbug,���������Ľ��շ��������,���Խ��յ�	
		                             //EIR_TXERIF��Զ�޷��ָ�һֱ����������ײ��ʼ��enc28j60
									 //ע��:�����⾭���޸�enc28j60�ײ�ķ��ͺ�����,����һֱ����,���Է���һ,���鲻ע��
	}
	/*task 3*/
	uip_main();				  //uip_poll ѭ����ѯ
	/*task 4*/
	sys_time_poll();
	/*task 5*/
	 
}
void loop_process_uart1(void)
{
	u16 datlen = 0;	
	if(rcv_usart1_end_flag)				  //Timer counts 6ms, then, usart1_end_flag turns high
	{
		//-ι������---------------
		feed_GSM_wakeup_softdog();   // ι����ʱ����AT������GSMģ�顱�� 
		feed_GSM_offline_softdog();	 // �ڶ�ʱ����AT�������GSMģ���Ƿ�����ʱ��������������⣬��˵��������
		//------------------------
		datlen = Rcv_Usart1_To_Array();	  //get data from the buffer
		if(datlen>0)
		{
		   	rcv_usart1_data_flg = 1;
		   	rcv_usart1_data_len = datlen;
		//����������������������������������������������Ӵ��ڽ��յ����ݡ�������������������������������������������������������������������������������������������������������������������������������
			//---------------------------------------------------------------------
			//  �ϵ��ʼ���������׶Σ�
			//	��һ�׶Σ�   �ȴ�����ϵ����
			//	�ڶ��׶Σ�   GSMģ����Խ��� AT������ζ�GSMģ���ʼ��
			//---------------------------------------------------------------------
			if( GSM_active_flag == 0 ) 			// �ȴ�GSM����
	  			wait_GSM_active();
			else if( init_GSM_end_flag == 0 )  	// �ȴ�GSM��ʼ��
				init_GSM();
			else 								// �Խ���������з���
				analyse_GSM_SM();
		}
		rcv_usart1_end_flag = 0;
	}
}
/*! \ loop_uart2
 *
 */
/*
void loop_process_uart2(void)
{
	u16 datlen = 0;					  //the variable for the array data's length
	if(rcv_usart2_end_flag)				  //Timer counts 6ms, then, usart1_end_flag turns high
	{
		datlen = Rcv_Usart2_To_Array();	  //get data from the buffer
		if(datlen>0)
		{
		   //������2���͹���������
		   //�����Դ���Ӳ��δ������
		   USART2_Put_Data(rcv_usart2_array,datlen);
		}
		rcv_usart2_end_flag = 0;
	}
}
*/
/*! \ sys_time_poll
 *
 */
void sys_time_poll(void)
{
	unsigned int i=0;
	if(time_1000ms == 1)
	{
		time_1000ms = 0;
	  	for(i = 0; i < UIP_CONNS; i++)
		{
		 	if((socket_keepalive[i].uip_kpl_time>0)&&(socket_keepalive[i].uip_kpl_rport!=0))
		   	{
			 	socket_keepalive[i].uip_kpl_time--;
			   	if(socket_keepalive[i].uip_kpl_time==0)	//ƥ��һ��
			   	{ 
                 	if(1)
					{
						socket_keepalive[i].uip_kpl_rport=socket_keepalive[i].uip_kpl_rport;   //������0��Ҫ��uip_appcall������ʹ��,���+-0.5s
						socket_keepalive[i].uip_kpl_type=0;   
						socket_keepalive[i].uip_kpl_time=0;
						socket_keepalive[i].uip_kpl_type=SOCKET_COMM_OFF; //keepalive��Ҫ�ر�socket  
						if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]:socket_keepalive[");
						if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
						if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("].uip_kpl_time==0  :) \r\n");
					} 
               	}
           	}			 			   
	 	}
	}	
}
/*! \ Uip_Poll
 *
 */
void uip_main(void)
{
	int i; 
	//u16 datlen = 0;				//the variable for the array data's length
	uip_len = etherdev_read();
	if(uip_len > 0)
	{
      	if(BUF->type == htons(UIP_ETHTYPE_IP)) 
      	{
    	  	uip_arp_ipin();
    	  	uip_input();
    	  	/* If the above function invocation resulted in data that
    	     should be sent out on the network, the global variable
    	     uip_len is set to a value > 0. */
      	  	if(uip_len > 0) 
          	{
    	     	uip_arp_out();
    	     	etherdev_send();
			}
      	} 
      	else if(BUF->type == htons(UIP_ETHTYPE_ARP)) 
	  	{
	      	uip_arp_arpin();
	      	/* If the above function invocation resulted in data that
	         should be sent out on the network, the global variable
	         uip_len is set to a value > 0. */
    	  	if(uip_len > 0) 
          	{
    	     	etherdev_send();
    	  	}
      	}
	}
	if(timer_expired(&periodic_timer)) 
	{
			
		timer_reset(&periodic_timer);
		if(CPU_DEBUG_TIMER) USART1_Put_String("timer_expired=periodic_timer\r\n");
		for(i = 0; i < UIP_CONNS; i++) 
		{
			uip_periodic(i);
			/* If the above function invocation resulted in data that
			should be sent out on the network, the global variable
			uip_len is set to a value > 0. */
		
			if(uip_len > 0)
			{
				uip_arp_out();
				etherdev_send();
			}
		}
		
		#if UIP_UDP
		for(i = 0; i < UIP_UDP_CONNS; i++) 
		{
			uip_udp_periodic(i);
			/* If the above function invocation resulted in data that
			should be sent out on the network, the global variable
			uip_len is set to a value > 0. */
		
			if(uip_len > 0) 
			{
				uip_arp_out();
				etherdev_send();
			}
		}
		#endif /* UIP_UDP */
		
		/* Call the ARP timer function every 10 seconds. */
		if(timer_expired(&arp_timer)) 
		{
			timer_reset(&arp_timer);
			uip_arp_timer();
			if(CPU_DEBUG_TIMER) USART1_Put_String("timer_expired=arp_timer\r\n");
		}
	}
}
/*! \ loop_uart1
 *
 */
/*! \ Init_Enc28j60_Chip
 *
 */
void Init_Enc28j60_Chip(void)
{
    enc28j60Init(mymac);  
}

//��Ϊtcp�ͻ��˳�ʼ��
void Tcp_Init(void)
{
    uip_ipaddr_t ipaddr ;//����IP���ͱ���


	uip_ipaddr(ipaddr, parasets.ips[4].ip[0], parasets.ips[4].ip[1], parasets.ips[4].ip[2], parasets.ips[4].ip[3]); //Զ��IP
	my_tcp_conn = uip_connect(&ipaddr, HTONS(RemotePort));//������Զ�̶˿�

}
/*! \ Init_uip
 *	//������ ֻ�� ������ main() ����ʱ���ù�һ��
 */
void Init_uip(void)				    
{  
   	uip_ipaddr_t ipaddr;
#ifdef UIP_STATIC_IP_ADDR
   	u8 i = 0;
#endif
   	static struct uip_eth_addr sTempAddr;

	uip_init();


#ifndef UIP_STATIC_IP_ADDR
	sTempAddr.addr[0] = mymac[0];
	sTempAddr.addr[1] = mymac[1];
	sTempAddr.addr[2] = mymac[2];
	sTempAddr.addr[3] = mymac[3];
	sTempAddr.addr[4] = mymac[4];
	sTempAddr.addr[5] = mymac[5];
	uip_setethaddr(sTempAddr);
	
	uip_ipaddr(ipaddr, 0, 0, 0, 0);
	uip_sethostaddr(ipaddr);
	uip_ipaddr(ipaddr, 0, 0, 0, 0);
	uip_setnetmask(ipaddr);
	dhcpc_init(&sTempAddr.addr[0], 6);
	dhcpc_request();
	if(CPU_DEBUG) USART1_Put_String("[system info]:dhcpc_request() Please wait a few seconds\r\n");
#endif


#ifdef UIP_STATIC_IP_ADDR
	sTempAddr.addr[0] = mymac[0];
	sTempAddr.addr[1] = mymac[1];
	sTempAddr.addr[2] = mymac[2];
	sTempAddr.addr[3] = mymac[3];
	sTempAddr.addr[4] = mymac[4];
	sTempAddr.addr[5] = mymac[5];
	uip_setethaddr(sTempAddr);

	uip_ipaddr(ipaddr, parasets.ips[0].ip[0], parasets.ips[0].ip[1], parasets.ips[0].ip[2], parasets.ips[0].ip[3]); //����Ip
	uip_sethostaddr(ipaddr);
	uip_ipaddr(ipaddr, parasets.ips[2].ip[0], parasets.ips[2].ip[1], parasets.ips[2].ip[2], parasets.ips[2].ip[3]); //��������
	uip_setdraddr(ipaddr);
	uip_ipaddr(ipaddr, parasets.ips[1].ip[0], parasets.ips[1].ip[1], parasets.ips[1].ip[2], parasets.ips[1].ip[3]); //������������
	uip_setnetmask(ipaddr);

	timer_set(&periodic_timer, ((CLOCK_CONF_SECOND / 2)/10)/1); //����TIM2 10ms periodic  500msִ��һ��  �ĳ�10msִ��һ��	  ȫ��g_RunTime����ʱ��ÿ10ms��1
	timer_set(&arp_timer, ((CLOCK_CONF_SECOND * 10)/10));	    //10sִ��һ��	ʵ����ÿ10msִ��һ������Ҫ��10 CLOCK_CONF_SECOND=1000Ĭ��

	uip_arp_init();

//	uip_listen(HTONS(myserverport));							//�����������Ķ˿�

	//---------------------------------------------------------------------
	//	�ڵ��Խ׶Σ�һֱ���ִ�������м��ӱ���
	//	���Խ�����ֻ���ڶ��ű�������ѯ�����ڵ�������������ط�  ���г�ʼ��

	Tcp_Init();													// �����ͻ���

	//---------------------------------------------------------------------

	if(CPU_DEBUG) USART1_Put_String("[system info]:static ip mode \r\n");
	/*mac*/
	if(CPU_DEBUG) USART1_Put_String("[system info]:mac=");
	if(CPU_DEBUG)
	{
      	for(i = 0; i < 6; i++)
      	{
        	Hex2HexStr(mymac[i]);
	    	if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
			if(i < 5) if(CPU_DEBUG) USART1_Put_String("-");
      	}
   	}
   	if(CPU_DEBUG) USART1_Put_String("\r\n");
   
    /*ip*/
   	if(CPU_DEBUG) USART1_Put_String("[system info]:ip=");
   	if(CPU_DEBUG)
   	{
      	for(i=0;i<4;i++)
      	{
        	Hex2Str(parasets.ips[0].ip[i]);
	    	if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
			if(i<3) if(CPU_DEBUG) USART1_Put_String(".");
      	}
   	}
   	if(CPU_DEBUG) USART1_Put_String("\r\n");
	/*Subnet mask*/
   	if(CPU_DEBUG) USART1_Put_String("[system info]:sm=");
   	if(CPU_DEBUG)
   	{
      	for(i=0;i<4;i++)
      	{
        	Hex2Str(parasets.ips[1].ip[i]);
	    	if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
			if(i<3) if(CPU_DEBUG) USART1_Put_String(".");
      	}
   	}
   	if(CPU_DEBUG) USART1_Put_String("\r\n");
	/*Gateway*/
   	if(CPU_DEBUG) USART1_Put_String("[system info]:gw=");
   	if(CPU_DEBUG)
   	{
      	for(i=0;i<4;i++)
      	{
        	Hex2Str(parasets.ips[2].ip[i]);
	    	if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
			if(i<3) if(CPU_DEBUG) USART1_Put_String(".");
      	}
   	}
   	if(CPU_DEBUG) USART1_Put_String("\r\n");
    /*port*/
   
   	if(CPU_DEBUG) USART1_Put_String("[system info]:port=");
   	if(CPU_DEBUG)
   	{
        U16_2Str(myserverport);
	    if(CPU_DEBUG) USART1_Put_String((unsigned char *)sssStr);
   	}
   	if(CPU_DEBUG) USART1_Put_String("\r\n");
#endif
}
/*! \ app_aborted
 *
 */
void app_aborted(void)
{  
	u8_t i;  
	if(CPU_DEBUG) USART1_Put_String("[system info]:app_aborted()=:( \r\n");

	 if(uip_conn->lport != HTONS(80))  //�ڼ���webclient ֮ǰ������һ������
	{
      	for(i = 0; i < UIP_CONNS; i++)
	  	{
			if(socket_keepalive[i].uip_kpl_rport==uip_conn->rport)   //  �� ���� webclient ֮ǰ�Ǳ�������
			{
				socket_keepalive[i].uip_kpl_rport=0;                   //����ǰclient�Ķ˿ڸ�ֵ
				socket_keepalive[i].uip_kpl_time=0;                    //��ֵ����
				socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;       //׼��...
				if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]: client socket active released=socket_closed[");
				if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
				if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("]:) \r\n"); 
				break;
			}
	  	}
  	}
  	uip_close();
  	uip_poll_ack_static=CLINT_ACKED_CLOSED;
}
/*! \ app_timedout
 *
 */
void app_timedout(void)
{ 
  	u8_t i;
  	if(CPU_DEBUG) USART1_Put_String("[system info]:app_timedout=:( \r\n");
  	if(uip_conn->lport!=HTONS(80))  //�ڼ���webclient ֮ǰ�Ǳ��д���
  	{
      	for(i = 0; i < UIP_CONNS; i++)
	  	{
			if(socket_keepalive[i].uip_kpl_rport==uip_conn->rport)     // �ڼ���webclient ֮ǰ�Ǳ��д���
			{
				socket_keepalive[i].uip_kpl_rport=0;                   //����ǰclient�Ķ˿ڸ�ֵ
				socket_keepalive[i].uip_kpl_time=0;                    //��ֵ����
				socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;       //׼��...
				if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]: client socket active released=socket_closed[");
				if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
				if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("]:) \r\n"); 
				break;
			}
	  	}
  	}
  	uip_close();
  	uip_poll_ack_static=CLINT_ACKED_CLOSED;
}
/*! \ app_closed
 *	  ������client�Ͽ���������ͷ�keepalive conn�ĵ���ʱ����
 */
void app_closed(void)
{
	u8_t i;
	uip_poll_ack_static=CLINT_ACKED_CLOSED;
	if(CPU_DEBUG) USART1_Put_String("[system info]:app_closed=:( \r\n");

	if(uip_conn->lport!=HTONS(80))	 	// �ڼ���webclient ֮ǰ�Ǳ��д���
   	{
      	for(i = 0; i < UIP_CONNS; i++)
	  	{
			if(socket_keepalive[i].uip_kpl_rport==uip_conn->rport)     //�ڼ���webclient ֮ǰ�Ǳ��д���
			{
				socket_keepalive[i].uip_kpl_rport=0;                   //����ǰclient�Ķ˿ڸ�ֵ
				socket_keepalive[i].uip_kpl_time=0;                    //��ֵ����
				socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;       //׼��...
				if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]: client socket active released=socket_closed[");
				if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
				if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("]:) \r\n"); 
				break;
			}
	  	}
   	}
}
/*! \ app_connected
 *	  ������client���Ӻ������keepalive�ĵ���ʱ����
 */
void app_connected(void)
{
    u16 i;
    if(CPU_DEBUG) USART1_Put_String("[system info]:app_connected=:) \r\n");

	uip_poll_ack_static=CLINT_ACKED_SYNACK;
	
	if(uip_conn->lport!=HTONS(80))  
	{
      	for(i=0;i<UIP_CONNS;i++)
	  	{
			if(socket_keepalive[i].uip_kpl_rport==uip_conn->rport)     
			{
				socket_keepalive[i].uip_kpl_rport=uip_conn->rport;    
				socket_keepalive[i].uip_kpl_time=TCP_KEEPALIVE_TIME;  //��ֵ����
				socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;      //���ͨ����,�����ͷ�
				if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]:socket_keepalive[");
				if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
				if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("].uip_kpl_time==TCP_KEEPALIVE_TIME(app_connected=resume) :) \r\n"); 
				break;
			}
	  	}
	  	if(i==UIP_CONNS)  //��ƥ���
	  	{
			for(i=0;i<UIP_CONNS;i++)
			{
		   		if(socket_keepalive[i].uip_kpl_rport==0)                 //���λ
		   		{
			  		socket_keepalive[i].uip_kpl_rport=uip_conn->rport;   
			  		socket_keepalive[i].uip_kpl_time=TCP_KEEPALIVE_TIME;  //��ֵ����
			  		socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;      //���ͨ����,�����ͷ� 
					if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]:socket_keepalive[");
					if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
					if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("].uip_kpl_time==TCP_KEEPALIVE_TIME(app_connected=new) :) \r\n");
					break;
		   		}
			}
	  	}
   	}
} 

/*! \ app_stop
 *
 */ 
void app_stop(void)
{
  u8_t i;
  if(CPU_DEBUG) USART1_Put_String("[system info]:app_stop=:) \r\n");
  if(uip_conn->lport!=HTONS(80))			   //�ڽ���webclient   uip_conn->lport
   {
      for(i=0;i<UIP_CONNS;i++)
	  {
		if(socket_keepalive[i].uip_kpl_rport==uip_conn->rport)     //�еǼǹ�  
		{
			socket_keepalive[i].uip_kpl_rport=0;                   //����ǰclient�Ķ˿ڸ�ֵ
			socket_keepalive[i].uip_kpl_time=0;                    //��ֵ����
			socket_keepalive[i].uip_kpl_type=SOCKET_COMM_ON;       //׼��...
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("[system info]: client socket active released=socket_closed[");
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_Char(i+0x30);
			if(CPU_DEBUG_KEEPALIVE) USART1_Put_String("]:) \r\n"); 
			break;
		}
	  }
   }
   uip_close();
   uip_poll_ack_static= CLINT_ACKED_CLOSED;

} 
/*! \ app_rexmit
 *
 */ 
void app_rexmit(void)
{
  if(CPU_DEBUG) USART1_Put_String("[system info]:app_rexmit=:) \r\n");
  // uip_poll_ack_static= CLINT_ACKED_CLOSED;
} 

//void tcp_senddata()
//{
//    uip_send(enc_send_buf, enc_send_size);
//}




/*! \ Uip_Appcall
 *	The application must be implemented as a C function, UIP_APPCALL(), that uIP calls whenever an event
occurs. Each event has a corresponding test function that is used to distinguish between different events.
	
	//by david :�������ӣ�
	struct uip_conn *my_tcp_conn;  										//tcp�ͻ�������

	//by david Web ���ӣ�


 */ 
void Uip_Appcall()  
{  	
  
  if ( uip_conn->lport  == my_tcp_conn->lport ) {			   //���Կڵ�UIP_APPCALL
		u16 i;
		u16 datlen ,uart1_debug_data_len;

    	if(uip_connected())  app_connected();
		if(uip_closed())     app_closed();
		if(uip_timedout())   app_timedout();
		if(uip_aborted())    app_aborted();
		//if(uip_stop())     app_stop();
		//if(uip_rexmit())	 app_rexmit();

    	switch(uip_conn->rport) 		
		{
			case HTONS(REMOTE_PORT):
				if(uip_connected())
    			{
        			tcp_server_flag = 0;

    			}

				if (uip_newdata())
    			{        
					tcp_data_Analyse();
    			}
				if (uip_newdata())	  
				{

           			if((uip_len > 0)&&(uip_len <= 1446))
		   			{
			 			// ----------------------------------
						// ��������������������������Ĵ���
						// ----------------------------------
						net_cmd_process(uip_appdata , uip_len);

			 			if(TCP2UART1)
			 			{
							//��������������������������������������������̫�����յ������ݣ�ͨ�����ڷ��ͳ�ȥ������������������������������������������
				 			//TCP���ݷ��͸�����1,����ķ�������ʱ�� 
				 			//���ÿ��Գ䵱TCP Ack�ĵȴ�ʱ��, 
				 			//1446��������ͨ�����ڷ��Ͳ��ᵼ��socket�˵ĵȴ�ACKʱ���쳣����
				 			//Q��TCP��ʱȷ�ϻ��ƹ���ԭ��
                 			//A��TCP��ʱȷ��ʱ��ͨ��Ϊ���ٺ��룬
				 			//������ӳ�ʱ�����б��Ķ�Ҫ���͵Ļ���
				 			//ack���ӵ����ݱ��Ķ�һ���ͣ����û�У���ô���ӳ�ʱ�䵽ʱ���͵�������ACK��
				 			//������Դ����ڵ�����,������ڸպ������ݴ����� ��uip_send(uip_appdata,uip_len); ��PSH,ACKһ��
			     			//USART1_Put_Data(uip_appdata, uip_len);		 //�����ԭ��ֱ��ת������䣬����һ��
							/*
							if(GSM_DEBUG) {
								snd_usart1_data_len = uip_len;
								memcpy(snd_usart1_array, uip_appdata, snd_usart1_data_len);
		    		 			USART1_Put_Data(snd_usart1_array, snd_usart1_data_len);
								Uart1SndDataFlag = 1;
							}
							*/

							//&*&*&*&*&*&*&*&*&*&�˶δ�����WebClient������ɺ�Ҫɾ��  
			 			}   //��������������������������������������������������������������������������������������������������������������������������������������������������������������
			 			//���¹��ܶ�����Ҫ����ʱ,�˴�����ʵ���Ƕ�uip_newdata()||(uip_rexmit())��Ack����

			 			if(1)//�Ƿ����Ӵ��Ĵ�������Ҫһ����
			 			{
				   	 		if(uip_poll_ack_static==CLINT_ACKED_SYNACK||uip_poll_ack_static == CLINT_ACKED_NORMAL || uip_poll_ack_static == CLINT_ACKED_CARRY)
					 		{
					     		uip_poll_ack_static=CLINT_NEWDAT_ACKED_CARRY;		  //���ñ��ΪPSH+ACKֵ
					 		}
			    	 
						}
					}
    			}

				if(uip_acked() || uip_poll() || uip_rexmit())		 
			    {   
					if(CPU_DEBUG_TIMER) USART1_Put_String("uip_poll()\r\n");
					datlen = 0;						
				
					//--------------------------
					//�鿴�Ƿ��д������ݷ���,ת����ETH�����Բο�
					//--------------------------
					uart1_debug_data_len = 0;
					
					if(Uart1SndDataFlag == 1 ) {  //����У���ת����ETH�����Բο���
						memcpy(tmp_eth_data_array , UART_DEBUG_SND_HEAD, strlen(UART_DEBUG_SND_HEAD));
						memcpy(tmp_eth_data_array + strlen(UART_DEBUG_SND_HEAD), snd_usart1_array, snd_usart1_data_len);
						memcpy(tmp_eth_data_array + strlen(UART_DEBUG_SND_HEAD) + snd_usart1_data_len, UART_DEBUG_SND_END, strlen(UART_DEBUG_SND_END) );
						uart1_debug_data_len = strlen(UART_DEBUG_SND_HEAD) + snd_usart1_data_len + strlen(UART_DEBUG_SND_END);
						Uart1SndDataFlag = 0;
						goto SEND;
					}
					//--------------------------
					//�Խ��յ����ݽ��д�����ʾ
					//�鿴�����Ƿ��� ���ݽ���,ת����ETH�����Բο�
					//--------------------------

		        	if(rcv_usart1_data_flg)		//  ���͵�ETH�������Բο�
		        	{
						datlen = rcv_usart1_data_len;
						if(datlen > 0)
						{
				   			//������1���͹���������
				   			if(memcmp(rcv_usart1_array, "~Cosmos Restart~",16) == 0)
				   			{
				      			if(CPU_DEBUG) USART1_Put_String("[system info]:form tcp uart1 ~Cosmos Restart~ = RST_CPU()\r\n");
				      			RST_CPU();
				   			}
				   			uip_len = datlen;
				   			if(uip_len >= 1500)
				   			{
				      			uip_len = 0; 
				      			if(CPU_DEBUG) USART1_Put_String("[system info]:form  uart1  uip_len>=1500\r\n");
				   			}
							//�������������������������������������ڽ��յ������ݣ�ͨ����̫���ӿڷ���ȥ��������������������������������
							memcpy(tmp_eth_data_array + uart1_debug_data_len, UART_DEBUG_RCV_HEAD, strlen(UART_DEBUG_RCV_HEAD));
							memcpy(tmp_eth_data_array + uart1_debug_data_len+ strlen(UART_DEBUG_RCV_HEAD), rcv_usart1_array, rcv_usart1_data_len);
							memcpy(tmp_eth_data_array + uart1_debug_data_len+ strlen(UART_DEBUG_RCV_HEAD) + rcv_usart1_data_len , UART_DEBUG_RCV_END, strlen(UART_DEBUG_RCV_END));
							uart1_debug_data_len += strlen(UART_DEBUG_RCV_HEAD) +  rcv_usart1_data_len + strlen(UART_DEBUG_RCV_END);
						}
	            		rcv_usart1_data_flg = 0;

						goto SEND;
	        		}
	        		if(webclient_data_flag)	{	//  ��������ȡ�� IP��ַ�Ĺ�������
						if(WEBCLIENT_DEBUG) {	

							memcpy(tmp_eth_data_array , CLIENT_SND_HEAD, strlen(CLIENT_SND_HEAD));
							memcpy(tmp_eth_data_array + strlen(CLIENT_SND_HEAD), webclient_data, webclient_data_len);
							memcpy(tmp_eth_data_array + strlen(CLIENT_SND_HEAD) + webclient_data_len, CLIENT_SND_END, strlen(CLIENT_SND_END) );
							uart1_debug_data_len = strlen(CLIENT_SND_HEAD) + webclient_data_len + strlen(CLIENT_SND_END);
						
							webclient_data_flag	= FALSE ;
								
							goto SEND;
						}
	        		}

					SEND:

					//----------------------------
					// This function is used to send out a single segment of TCP data. Only applications that have been invoked
					// by uIP for event processing can send data.
					//----------------------------
					//���Խ׶Σ��Ѵ�������ȫ�����ͳ�ȥ
					if(GSM_DEBUG && uart1_debug_data_len>0) {
						memcpy(uip_appdata , tmp_eth_data_array, uart1_debug_data_len);
   						uip_send(uip_appdata, uart1_debug_data_len);
					}

	   				uip_poll_ack_static = 3; 		 
	   				for(i = 0; i < UIP_CONNS; i++) {    
						socket_keepalive[i].uip_kpl_time = TCP_KEEPALIVE_TIME;  //��ֵ����	 
					}
				
				}
			
				if(uip_closed())
			    {
		    	    tcp_server_flag++;
		        	if(tcp_server_flag == 2)
		        	{
		            	uip_ipaddr_t ipaddr;					//����IP���ͱ���
		            	uip_ipaddr(ipaddr, parasets.ips[4].ip[0], parasets.ips[4].ip[1], parasets.ips[4].ip[2], parasets.ips[4].ip[3]); 	//Զ��IP
		            	my_tcp_conn = uip_connect(&ipaddr, HTONS(RemotePort));	
		            	tcp_server_flag = 0;
		        	}
		    	}
				if( uip_aborted())
		    	{
		        	uip_ipaddr_t ipaddr;						//����IP���ͱ���
		        	uip_ipaddr(ipaddr, parasets.ips[4].ip[0], parasets.ips[4].ip[1], parasets.ips[4].ip[2], parasets.ips[4].ip[3]); 		//Զ��IP
		        	my_tcp_conn = uip_connect(&ipaddr, HTONS(RemotePort));		
				}
				
		    	break;
		
		    default:
			    break;
 		}
  	}		  //�������� UIP_APPCALL
//----------------by david 
	//  wevclient appcall -----
    else if( uip_conn->lport  == webclient_lport() ) { 	  // webclient ��UIP_APPCALL;   HTONS(webclient_port())
		//-----------------------------------------
  		webclient_appcall();
	}
//------smtp ----------by david 

    else if( uip_conn->lport  == smtp_lport() ) { 	  // webclient ��UIP_APPCALL;   HTONS(webclient_port())
		//debug_info_show("smtp UIP_APPCALL.\r\n",19);
  		smtp_appcall();
	} 

	else {
		char info[70];
		char tip[] = "lport call ?.\r\n";
		u8	len  = 0;

		lport2ripStr(htons(uip_conn->lport) , uip_conn->ripaddr, htons(uip_conn->rport), info);
		len = strlen(info);

  		memcpy(info + len, tip , strlen(tip));
  		len += strlen(tip);
  		info[len ] ='\0';

  		debug_info_show(info,len);
		//---------------------------------
		uip_close();

	}
}
// ------------------------------------------------------------------
//  local port remote ip string 
// ------------------------------------------------------------------
void lport2ripStr(u16_t lport , uip_ipaddr_t ripaddr, u16_t rport ,char *port_ip_str)
{
	char portStr[7],ipstr[20];
	u8	len  = 0;

	itoa(lport ,portStr,10);  
	IpU16ToStr(ripaddr, ipstr );

	len = 0;
	memcpy(port_ip_str , portStr , strlen(portStr));
	len += strlen(portStr);
  
	memcpy(port_ip_str + len , "->" , 2);
	len += 2;

	memcpy(port_ip_str + len , ipstr , strlen(ipstr));
	len += strlen(ipstr) ;

	itoa(rport ,portStr,10);  

	memcpy(port_ip_str + len , portStr , strlen(portStr));
	len += strlen(portStr) ;

	port_ip_str[len ] ='\0';

}
// ------------------------------------------------------------------
//  extract the value of var from net data 
// ------------------------------------------------------------------
bool Extract_N_V_Para(void *rawdata, u16 datalen, char *name, char *value)
{
	int i=0, j=0 ;
	char *data ;
	//search for para name and value of para ---------------
	data = (char*)rawdata ;
	for(i=0; i<datalen; i++)
		if( data[i] == '=')  //��ʽ�жϣ��Ƿ��и�ֵ���	
			break;
	if(i>=(strlen(NET_CMD_set) + PARA_L_CMD_EN + 2))	return FALSE;			   //������Ƿ񳬳�

	memcpy(name, data + strlen(NET_CMD_set), i-strlen(NET_CMD_set));	 //�����洢
	name[i-strlen(NET_CMD_set)] = '\0';
	
	for(j=0; j<PARA_L_WEB; j++)
		if( data[i+1+j] == '\r')  //�Ƿ��лس����У��������ý�����־	
			break;
	if( j >= PARA_L_WEB )	return FALSE;				//����ֵ�Ƿ񳬳� (��Ĳ�����Web ��صĲ���

	memcpy(value, data +i+1 , j);
	value[j] = '\0';
	
	//------ para name and value of para end ----------------
	return TRUE;
}
// ------------------------------------------------------------------
//  phone is or no valid .
// ------------------------------------------------------------------
bool IsValidPhone(char *phone)
{
	int i = 0;
	if(phone[0] == '+' ) {		//+nnnnnnnnnnn	��λ+
		for(i=1; i<	strlen(phone); i++) 	 //��λ+
			if(phone[i] < '0' || phone[i] > '9')
				break;
		if(i<strlen(phone))
			return FALSE;
		else
			return TRUE;
	}
	else {						//nnnnnnnnnnnnn	  ��λ����+
		for(i=0; i<	strlen(phone); i++) 	   //��λ����+,��ֻ��������
			if(phone[i] < '0' || phone[i] > '9')
				break;
		if(i<strlen(phone))
			return FALSE;
		else
			return TRUE;
	}
}

// ------------------------------------------------------------------
//  net command set para and save to EEPROM .
// ------------------------------------------------------------------
bool net_cmd_set_para(void *rawdata, u16 datalen)
{

	int i=0 ;
	char paraName[PARA_L_CMD_EN+1];
	char paraValue[PARA_L_WEB+1]; 

	//������ÿ����Ƿ��� ����̬
	if (now_status() != STATUS_CONFIG) {
		char info[] = "Now config switch is not in config status,set is unsuccessful !";
		debug_info_show(info,strlen(info));
		return FALSE;
	}

	//���������ơ�ֵ�ĺ�����
	if( Extract_N_V_Para(rawdata, datalen, paraName, paraValue)== FALSE ) {
		char info[] = "the name or value of para are error!";
		debug_info_show(info,strlen(info));
		return FALSE;
	}

	//--- search for IP para ------------
	for(i=0;i<PARA_ACCOUNT_IP ; i++)  //��IP ��������Ѱ�� 
		if( memcmp(paraName, parasets.ips[i].nm, strlen(parasets.ips[i].nm)) == 0) 	
			break;
	if( i<PARA_ACCOUNT_IP  ) {		   //�ҵ��� �������ַ
		IP_PARA_SET ip_para;

		ip_para.vaddr = parasets.ips[i].vaddr ;

		if(IpStrToU8(paraValue,ip_para.ip)) {
			save_para_IP(&ip_para) ;
			goto SETOK;
		}
		else {
			char info[] = "ip addr is invalid !";
			debug_info_show(info,strlen(info));
			return FALSE;

		}
	}
	//--- search for phone  para ------------
	for(i=0;i<PARA_ACCOUNT_PHONE ; i++) 
		if( memcmp(paraName, parasets.tels[i].nm, strlen(parasets.tels[i].nm)) == 0) 	
			break;

	if( i<PARA_ACCOUNT_PHONE ) {	  //�ҵ��� �������ַ
		
		if(IsValidPhone(paraValue))	{
			PHONE_PARA_SET	phone_data;
			u16 len ;

			phone_data.vaddr = parasets.tels[i].vaddr ;

			memcpy(phone_data.tel, paraValue, strlen(paraValue));

			len = strlen(paraValue);
			if( len%2!=0) {			  // �ճ����ֱ��� flash�洢
				phone_data.tel[len  ] = '\0';
				phone_data.tel[len+1] = '\0';
			}

			save_para_phone(&phone_data) ;
			goto SETOK;
		}
		else {
			char info[] = "phone is invalid !";
			debug_info_show(info,strlen(info));
			return FALSE;

		}
	}		
	//--- search for web para ------------
	for(i=0;i<PARA_ACCOUNT_WEB ; i++) 
		if( memcmp(paraName, parasets.webs[i].nm, strlen(parasets.webs[i].nm)) == 0) 	
			break;

	if( i<PARA_ACCOUNT_WEB ) {

		u16 len ;
		WEB_PARA_SET	web_data;

		web_data.vaddr = parasets.webs[i].vaddr ;		  //�ҵ��� �������ַ
		memcpy(web_data.val, paraValue, strlen(paraValue));

		len = strlen(paraValue);
		if( len%2!=0) {			  // �ճ����ֱ��� flash�洢
			web_data.val[len  ] = '\0';
			web_data.val[len+1] = '\0';
		}

		save_para_URL(&web_data) ;

		goto SETOK;
	}
	//--- search for email para ------------
	for(i=0;i<PARA_ACCOUNT_EMAIL ; i++) 
		if( memcmp(paraName, parasets.emails[i].nm, strlen(parasets.emails[i].nm)) == 0) 	
			break;

	if( i<PARA_ACCOUNT_EMAIL ) {

		u16 len ;
		EMAIL_PARA_SET	email_data;

		email_data.vaddr = parasets.emails[i].vaddr ;		  //�ҵ��� �������ַ
		memcpy(email_data.val, paraValue, strlen(paraValue));

		len = strlen(paraValue);
		if( len%2!=0) {			  // �ճ����ֱ��� flash�洢
			email_data.val[len  ] = '\0';
			email_data.val[len+1] = '\0';
		}

		save_para_email(&email_data) ;

		goto SETOK;
	}
	else {											//���������ò������ж�û���ҵ�
		char info[] = "the name is not exist!";
		debug_info_show(info,strlen(info));
		return FALSE;
	}
	SETOK:
	{
		char info[] = "para set is OK !";
		debug_info_show(info,strlen(info));
		return TRUE;
	}
}
// ------------------------------------------------------------------
//  net command read EEPROM and show .
// ------------------------------------------------------------------
void net_cmd_get_para(void *rawdata, u16 datalen)
{
	int i=0, j=0 ;
	//--- search for IP para ------------
	for(i=0;i<PARA_ACCOUNT_IP ; i++)  //��IP ��������Ѱ�� 
		if( memcmp((u8*)rawdata + strlen(NET_CMD_get), parasets.ips[i].nm, strlen(parasets.ips[i].nm)) == 0) 	
			break;

	if( i<PARA_ACCOUNT_IP ) {	
		IP_PARA_SET	ip_data;
		char ip_ascii[10];
		webclient_data_len = 0;

		ip_data.vaddr = parasets.ips[i].vaddr ;
		read_para_IP(&ip_data)	;

		for(j=0; j<PARA_L_IP ; j++)  {
			itoa(ip_data.ip[j],ip_ascii,10) ;
			memcpy(webclient_data + webclient_data_len,ip_ascii , strlen(ip_ascii)) ; 
			webclient_data_len += strlen(ip_ascii);

			memcpy(webclient_data + webclient_data_len,"." , 1) ; 
			webclient_data_len ++ ;
		}
		memcpy(webclient_data + webclient_data_len, "\r\n" , 2) ; 
		webclient_data_len += 2;
		webclient_data_flag	= TRUE ;
		return;
	}
	//--- search for phone  para ------------
	for(i=0;i<PARA_ACCOUNT_PHONE ; i++) 
		if( memcmp((u8*)rawdata + strlen(NET_CMD_get), parasets.tels[i].nm, strlen(parasets.tels[i].nm)) == 0) 	
			break;

	if( i<PARA_ACCOUNT_PHONE ) {	
		PHONE_PARA_SET	phone_data;
		webclient_data_len = 0;
	
		phone_data.vaddr = parasets.tels[i].vaddr ;
		read_para_phone(&phone_data)	;

		memcpy(webclient_data ,phone_data.tel , strlen(phone_data.tel)) ; 
		webclient_data_len += strlen(phone_data.tel);

		memcpy(webclient_data + webclient_data_len, "\r\n" , 2) ; 
		webclient_data_len += 2;
		webclient_data_flag	= TRUE ;
		return;
	}
		//--- search for web para ------------
	for(i=0;i<PARA_ACCOUNT_WEB ; i++) 
		if( memcmp((u8*)rawdata + strlen(NET_CMD_get), parasets.webs[i].nm, strlen(parasets.webs[i].nm)) == 0) 	
			break;

	if( i<PARA_ACCOUNT_WEB ) {	
		WEB_PARA_SET	web_data;
		webclient_data_len = 0;

		web_data.vaddr = parasets.webs[i].vaddr ;
		read_para_URL(&web_data)	;

		memcpy(webclient_data ,web_data.val , strlen(web_data.val)) ; 
		webclient_data_len += strlen(web_data.val);

		memcpy(webclient_data + webclient_data_len, "\r\n" , 2) ; 
		webclient_data_len += 2;
		webclient_data_flag	= TRUE ;
		return;
	}
		//--- search for email para ------------
	for(i=0;i<PARA_ACCOUNT_EMAIL ; i++) 
		if( memcmp((u8*)rawdata + strlen(NET_CMD_get), parasets.emails[i].nm, strlen(parasets.emails[i].nm)) == 0) 	
			break;

	if( i<PARA_ACCOUNT_EMAIL ) {	
		EMAIL_PARA_SET	email_data;
		webclient_data_len = 0;

		email_data.vaddr = parasets.emails[i].vaddr ;
		read_para_email(&email_data)	;

		memcpy(webclient_data ,email_data.val , strlen(email_data.val)) ; 
		webclient_data_len += strlen(email_data.val);

		memcpy(webclient_data + webclient_data_len, "\r\n" , 2) ; 
		webclient_data_len += 2;
		webclient_data_flag	= TRUE ;
		return;
	}

		//--- all of para is not found .------------
	else {		
		char info[] = "the para not exist!\r\n" ;
		webclient_data_len = 0;
			
		memcpy(webclient_data ,info , strlen(info)) ; 
		webclient_data_len += strlen(info);

		webclient_data_flag	= TRUE ;
	}		

}
/*
*  net command procese
*/
void net_cmd_process(void *rawdata, u16 datalen)
{
	//����Զ��TCP��λ������		 		
	if(memcmp(rawdata,"~Cosmos Restart~",16) == 0)				
	{
   		if(CPU_DEBUG) USART1_Put_String("[system info]:form tcp client ~Cosmos Restart~ = RST_CPU()\r\n");
    		RST_CPU();
	}
	//-----------------------------------------------------
	// �������� WebClient ����
	//-----------------------------------------------------
	if( memcmp(rawdata,"clientstart",11) == 0)	{			//���� WebClient
		Web_Link_Init();
		memcpy(requestIPphone, phonelist.t1 , strlen(phonelist.t1));		//�洢��������� �ֻ�����
		return;
	}
	//-------------------------------------------------------------------------------------

	if( memcmp(rawdata,"help",4) == 0)	{			//����
		
		u16 len = 0 , i =0;
	
		//��ʾ����״̬		
		if (now_status() == STATUS_CONFIG) {
			char info_C[] = "��ǰ<����̬><Configing Status>���������á�\r\n";
			memcpy(webclient_data + len , info_C , strlen(info_C));
			len += strlen(info_C);
		}
		else {
			char info_R[] = "��ǰ<����̬><Running Status> ���ɴ洢����\r\n";
			memcpy(webclient_data + len , info_R , strlen(info_R));
			len += strlen(info_R);
		}

		//��ʾ�����ʽ
		memcpy(webclient_data + len , NET_CMD_HELP0 , strlen(NET_CMD_HELP0));
		len += strlen(NET_CMD_HELP0);
		memcpy(webclient_data + len , NET_CMD_HELP1 , strlen(NET_CMD_HELP1));
		len += strlen(NET_CMD_HELP1);
		memcpy(webclient_data + len , NET_CMD_HELP2 , strlen(NET_CMD_HELP2));
		len += strlen(NET_CMD_HELP2);
		memcpy(webclient_data + len , NET_CMD_HELP3 , strlen(NET_CMD_HELP3));
		len += strlen(NET_CMD_HELP3);
		memcpy(webclient_data + len , NET_CMD_HELP4 , strlen(NET_CMD_HELP4));
		len += strlen(NET_CMD_HELP4);
		memcpy(webclient_data + len , NET_CMD_HELP5 , strlen(NET_CMD_HELP5));
		len += strlen(NET_CMD_HELP5);
		memcpy(webclient_data + len , NET_CMD_HELP6 , strlen(NET_CMD_HELP6));
		len += strlen(NET_CMD_HELP6);
		memcpy(webclient_data + len , NET_CMD_HELP7 , strlen(NET_CMD_HELP7));
		len += strlen(NET_CMD_HELP7);
		memcpy(webclient_data + len , NET_CMD_HELP8 , strlen(NET_CMD_HELP8));
		len += strlen(NET_CMD_HELP8);
		memcpy(webclient_data + len , NET_CMD_HELP9 , strlen(NET_CMD_HELP9));
		len += strlen(NET_CMD_HELP9);


		//��ʾ�������
		for(i = 0; i< PARA_ACCOUNT_IP ;i++) {
			memcpy(webclient_data + len , "  " , 2);
			len +=2 ;
			memcpy(webclient_data + len , parasets.ips[i].nm , strlen(parasets.ips[i].nm));
			len += strlen(parasets.ips[i].nm);
											 
			memcpy(webclient_data + len , parasets.ips[i].cn , strlen(parasets.ips[i].cn));
			len += strlen(parasets.ips[i].cn);

			memcpy(webclient_data + len , "\r\n" , 2);
			len +=2;
		}
		for(i = 0; i< PARA_ACCOUNT_PHONE ;i++) {
			memcpy(webclient_data + len , "  " , 2);
			len +=2 ;
			memcpy(webclient_data + len , parasets.tels[i].nm , strlen(parasets.tels[i].nm));
			len += strlen(parasets.tels[i].nm);								 

			memcpy(webclient_data + len , parasets.tels[i].cn , strlen(parasets.tels[i].cn));
			len += strlen(parasets.tels[i].cn);								 

			memcpy(webclient_data + len , "\r\n" , 2);
			len +=2;
		}
		for(i = 0; i< PARA_ACCOUNT_WEB ;i++) {
			memcpy(webclient_data + len , "  " , 2);
			len +=2 ;
			memcpy(webclient_data + len , parasets.webs[i].nm , strlen(parasets.webs[i].nm));
			len += strlen(parasets.webs[i].nm);								 

			memcpy(webclient_data + len , parasets.webs[i].cn , strlen(parasets.webs[i].cn));
			len += strlen(parasets.webs[i].cn);								 

			memcpy(webclient_data + len , "\r\n" , 2);
			len +=2;
		}
		for(i = 0; i< PARA_ACCOUNT_EMAIL ;i++) {
			memcpy(webclient_data + len , "  " , 2);
			len +=2 ;
			memcpy(webclient_data + len , parasets.emails[i].nm , strlen(parasets.emails[i].nm));
			len += strlen(parasets.emails[i].nm);								 

			memcpy(webclient_data + len , parasets.emails[i].cn , strlen(parasets.emails[i].cn));
			len += strlen(parasets.emails[i].cn);								 

			memcpy(webclient_data + len , "\r\n" , 2);
			len +=2;
		}

		webclient_data_len = len;
		webclient_data_flag	= TRUE ;
		return;

	}

	//-------------------------------------------------------------------------------------
	if( memcmp(rawdata,NET_CMD_SHOW_MEM_PARA,strlen(NET_CMD_SHOW_MEM_PARA)) == 0)	{	//��ʾ��ǰ���в���
		show_mem_para();		
		return;
	}

	if( memcmp(rawdata,NET_CMD_SHOW_FLASH_PARA,strlen(NET_CMD_SHOW_FLASH_PARA)) == 0)	{	//��ʾflash����
		show_flash_para();		
		return;
	}

	if( memcmp(rawdata,NET_CMD_SAVE_MEM_TO_FLASH,strlen(NET_CMD_SAVE_MEM_TO_FLASH)) == 0)	{	//��flash�����ڴ�
		save_mem_to_flash();
		return;
	}

	if( memcmp(rawdata,NET_CMD_READ_FLASH_TO_MEM,strlen(NET_CMD_READ_FLASH_TO_MEM)) == 0)	{	//�洢���в�������
		read_flash_to_mem();
		return;
	}
	
	if( memcmp(rawdata,NET_CMD_COMP_FALSH,strlen(NET_CMD_COMP_FALSH)) == 0)	{			//�Ƚ�flash���в���
		CompareFlashWithMem();
		return;
	}

	// set para and save to eeprom 
	if( memcmp(rawdata,NET_CMD_set,strlen(NET_CMD_set)) == 0)	{	//�洢ĳһ����
		net_cmd_set_para(rawdata,datalen) ;
		return;
	}

	// get para from eeprom and show 					   //��ȡĳһ����
	if( memcmp(rawdata,NET_CMD_get,strlen(NET_CMD_get)) == 0)	{	
		net_cmd_get_para(rawdata,datalen) ;
		return;
	}

	if( memcmp(rawdata,	NET_CMD_SHOW_ACT_WEB,strlen(NET_CMD_SHOW_ACT_WEB)) == 0)	{	
		ShowActiveWeb() ;
		return;
	}
	//---------------------------------
	if( memcmp(rawdata,"show mem tel",strlen("show mem tel")) == 0)	{	
		ShowMemTelUnicode();
		//TelAsciiToUnicode(parasets.tels[0].tel, phonelist.t1);
		return;
	}

	if( memcmp(rawdata,"send email",strlen("send email")) == 0)	{	
		uip_ipaddr_t *ipaddr ;
		char smtpSvr[PARA_L_WEB] ;

		getSmtpSvr(smtpSvr, parasets.emails[0].val);

		ipaddr = (uip_ipaddr_t *)LookupIP(smtpSvr);	

		if( ipaddr != NULL )	{  // DNS �Ѿ�������

			strcpy(EmailSubject,"Test send email no first time.");
			strcpy(EmailMsg,    "msg txt.\r\n");

			smtp_configure("ut.com", ipaddr);
			smtp_init();
			GetEmailUserPW();
			SendEmail_163(EmailSubject, EmailMsg);
		}
		return;					  //DNSû�н��������˳��ȴ���
	}

	//�Ҳ�����������ʾ��ʾ��
	{
		char info[]=	NET_CMD_NONE;
		debug_info_show(info,strlen(info));
		return;
	}
}
void getSmtpSvr(char *smtpSvr, char *from)
{
	u8 i = 0 ,len = 0;
	
	len = strlen(from);
	for(i = 0; i< len ; i ++) 		
		if(from[i] == '@' ) break;
	
	if(i < len ) {
		memcpy(smtpSvr, "smtp." , 5);
		memcpy(smtpSvr + 5 , from+i+1 , len-i-1);
		smtpSvr[5+len-i-1]='\0';
	}
	else {
		char info[] = "smtp server is invalid .\r\n";
		debug_info_show(info,strlen(info));
	}
}

/*! \ Udp_Appcall
 *																														  
 */
void Udp_Appcall(void)  
{  

    switch(uip_udp_conn->rport) 
	{
	  case HTONS(67):
	  case HTONS(68):
           dhcpc_appcall();
	       break;
	  case HTONS(53):
	  	   resolv_appcall();	//DNS Udp_Appcall();
		   break;
	  default:
	       break; 
	}
} 


void dhcpc_configured(const struct dhcpc_state *s)
{
    u8 i;
	uip_ipaddr_t ipaddr;

    uip_sethostaddr(&s->ipaddr);
    uip_setnetmask(&s->netmask);
    uip_setdraddr(&s->default_router);

	memcpy(parasets.ips[0].ip,s->ipaddr,4);
	memcpy(parasets.ips[1].ip,s->netmask,4);
	memcpy(parasets.ips[2].ip,s->default_router,4);


	uip_ethaddr.addr[0] = mymac[0];
	uip_ethaddr.addr[1] = mymac[1];
	uip_ethaddr.addr[2] = mymac[2];
	uip_ethaddr.addr[3] = mymac[3];
	uip_ethaddr.addr[4] = mymac[4];
	uip_ethaddr.addr[5] = mymac[5];
	uip_setethaddr(uip_ethaddr);
	
	uip_ipaddr(ipaddr, parasets.ips[0].ip[0], parasets.ips[0].ip[1], parasets.ips[0].ip[2], parasets.ips[0].ip[3]);      //����Ip
	uip_sethostaddr(ipaddr);
	uip_ipaddr(ipaddr, parasets.ips[1].ip[0], parasets.ips[1].ip[1], parasets.ips[1].ip[2], parasets.ips[1].ip[3]);      //������������
	uip_setnetmask(ipaddr);
	uip_ipaddr(ipaddr, parasets.ips[2].ip[0], parasets.ips[2].ip[1], parasets.ips[2].ip[2], parasets.ips[2].ip[3]);      //��������
	uip_setdraddr(ipaddr);
	
	timer_set(&periodic_timer, ((CLOCK_CONF_SECOND / 2)/10)/1);  //����TIM2 10ms periodic  500msִ��һ��  �ĳ�10msִ��һ��	  ȫ��g_RunTime����ʱ��ÿ10ms��1
	timer_set(&arp_timer, ((CLOCK_CONF_SECOND * 10)/10));	    //10sִ��һ��	ʵ����ÿ10msִ��һ������Ҫ��10 CLOCK_CONF_SECOND=1000Ĭ��
	uip_arp_init();
//   uip_listen(HTONS(myserverport));							    //�����������Ķ˿�
	Tcp_Init();

	if(CPU_DEBUG) USART1_Put_String("[system info]:dhcpc_configured()=successed \r\n");
	if(CPU_DEBUG) USART1_Put_String("[system info]:dhcp  mode \r\n");
	/*mac*/
   if(CPU_DEBUG) USART1_Put_String("[system info]:mac=");
   if(CPU_DEBUG)
   {
      for(i=0;i<6;i++)
      {
        Hex2HexStr(mymac[i]);
	    if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
		if(i<5) if(CPU_DEBUG) USART1_Put_String("-");
      }
   }
   if(CPU_DEBUG) USART1_Put_String("\r\n");
   
    /*ip*/
   if(CPU_DEBUG) USART1_Put_String("[system info]:dhcp-ip=");
   if(CPU_DEBUG)
   {
      for(i=0;i<4;i++)
      {
        Hex2Str(parasets.ips[0].ip[i]);
	    if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
		if(i<3) if(CPU_DEBUG) USART1_Put_String(".");
      }
   }
   if(CPU_DEBUG) USART1_Put_String("\r\n");
	/*Subnet mask*/
   if(CPU_DEBUG) USART1_Put_String("[system info]:dhcp-sm=");
   if(CPU_DEBUG)
   {
      for(i=0;i<4;i++)
      {
        Hex2Str(parasets.ips[1].ip[i]);
	    if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
		if(i<3) if(CPU_DEBUG) USART1_Put_String(".");
      }
   }
   if(CPU_DEBUG) USART1_Put_String("\r\n");
	/*Gateway*/
   if(CPU_DEBUG) USART1_Put_String("[system info]:dhcp-gw=");
   if(CPU_DEBUG)
   {
      for(i=0;i<4;i++)
      {
        Hex2Str(parasets.ips[2].ip[i]);
	    if(CPU_DEBUG) USART1_Put_String((unsigned char *)HEXStr);
		if(i<3) if(CPU_DEBUG) USART1_Put_String(".");
      }
   }
   if(CPU_DEBUG) USART1_Put_String("\r\n");
    /*port*/
   
   if(CPU_DEBUG) USART1_Put_String("[system info]:port=");
   if(CPU_DEBUG)
   {
        U16_2Str(myserverport);
	    if(CPU_DEBUG) USART1_Put_String((unsigned char *)sssStr);
   }
   if(CPU_DEBUG) USART1_Put_String("\r\n");
   if(CPU_DEBUG) USART1_Put_String("[system info]::) \r\n");
   if(CPU_DEBUG) USART1_Put_String("[system info]:********************************************************/ \r\n");
}
//*********************************************************************************************************
/*
* Web  ���ӵĳ�ʼ��
*/
//*********************************************************************************************************
void Web_Link_Init(void)
{
  	uip_ipaddr_t *ipaddr;

	WEB_URL ActWeb ;

	GetActWeb(&ActWeb) ;
	ipaddr =  (uip_ipaddr_t *)LookupIP(ActWeb.URL);

	if(ipaddr != NULL ) 	// DNS�Ѿ�������
	   	webclient_get(ActWeb.URL, 80, ActWeb.file);   
	else
		return ;   			// �ȴ�DNS����
}

void resolv_found(char *name, u16_t *ipaddr)
{

  char ipString[20] ;

  if(ipaddr == NULL) {
	
    //printf("Host '%s' not found.\n", name);
	
   	if(WEBCLIENT_DEBUG)	{	
	    char info[] = "Host not found or DNS set ERR."  ;
		webclient_data_len = strlen(info) ;	
		memcpy(webclient_data , info, webclient_data_len);
		webclient_data_flag	= TRUE ;		
	}
	

  } else {

  	WEB_URL ActWeb ;
	GetActWeb(&ActWeb) ;
	//����DNS �Ƿ���ȷ�׶Σ�
   	if(WEBCLIENT_DEBUG)	{	
	    char info[] = " have been found."  ;

		IpU16ToStr(ipaddr,ipString);

		webclient_data_len = strlen(name) ;	
		memcpy(webclient_data , name , webclient_data_len);
		memcpy(webclient_data + webclient_data_len , ipString , strlen(ipString));
		memcpy(webclient_data + webclient_data_len + strlen(ipString), info , strlen(info));

		webclient_data_len += strlen(ipString)+strlen(info);

		webclient_data_flag	= TRUE ;		
	}
	//----�ҵ�IP��ַ-----------------------------
   	if(memcmp(name, ActWeb.URL,strlen(name))==0 ) {		// webclient IP
		webclient_get(ActWeb.URL, 80, ActWeb.file);
	}
	else {												// smtp IP
		smtp_configure("ut.com", ipaddr);
		smtp_init();
		GetEmailUserPW();
		//------------------------------------
		SendEmail_163(EmailSubject, EmailMsg);
	}
  }
}

void webclient_closed(void)
{
  //my_printf2("connection closed\n");
   	if(WEBCLIENT_DEBUG)	{	
		char info[70];
		char CErrInfo[] = " connection closed .\r\n";
		u8_t	len  = 0;

		lport2ripStr(htons(uip_conn->lport) , uip_conn->ripaddr, htons(uip_conn->rport), info);
		len = strlen(info);

		memcpy(info + len, CErrInfo , strlen(CErrInfo));
		len += strlen(CErrInfo);
		info[len ] ='\0';

		debug_info_show(info,len);
	}
  	uip_close();
	webclient_close();
}

void webclient_aborted(void)
{
  //my_printf2("connection aborted\n");

   	if(WEBCLIENT_DEBUG)	{	
		char info[] = "weblink aborted and closed.\r\n";   	
        debug_info_show(info,strlen(info));
	}
  	uip_close();
	webclient_close();
}

void webclient_timedout(void)
{

  //my_printf2("connection timed out\n");

   	if(WEBCLIENT_DEBUG)	{	//  ��������ȡ�� IP��ַ�Ĺ�������
		char info[70];
		char  tip[] = "weblink timeout & closed.\r\n";   	
		u8	len  = 0;

		lport2ripStr(htons(uip_conn->lport) , uip_conn->ripaddr, htons(uip_conn->rport), info);
		len = strlen(info);

		memcpy(info + len, tip , strlen(tip));
		len += strlen(tip);
		info[len ] ='\0';

		debug_info_show(info,len);
	}
  	uip_close();
	webclient_close();
}

void webclient_connected(void)
{
//  my_printf2("connected, waiting for data...\n");

	if(WEBCLIENT_DEBUG)	{	
		char info[] = "WebCS.host connected.\r\n";
        debug_info_show(info,strlen(info));
	}
}

void webclient_datahandler(char *data, u16_t len)
{

   //static uint16_t cnt;
   char *ipAddr;
	
	WEB_URL ActWeb ;
	GetActWeb(&ActWeb) ;
	
	// my_printf2("got %d bytes of data.counter =%d \n", len,++cnt);

	if( data==NULL ) {
		uip_close();
		return ;	
	}
	
   	if(WEBCLIENT_DEBUG)	{	//  ��������ȡ�� IP��ַ�Ĺ�������
		webclient_data_len = len ;	
		memcpy(webclient_data , data, webclient_data_len);
		webclient_data_flag	= TRUE ;		
								   
	}
	
	//�������ģ����չؼ���Ѱ�� IP ��ַ
	ipAddr = ParsePageIpAddr( data, ActWeb.s_str, ActWeb.e_str);

	if(	ipAddr != NULL ) {

		strcpy(EmailSubject,"Ip:");
		strcpy(EmailSubject+3,ipAddr);
		strcpy(EmailMsg,"OK! connection closed.");

		if(requestIPphone[0]!='\0' ) {
			sendIP2phone(requestIPphone,ipAddr); //�绰ѹ�����Ͷ��У�
			requestIPphone[0] = '\0';		//��յ绰��Ϊ��һ��������׼��
		}

	   	if(WEBCLIENT_DEBUG)	{	//  ��������ȡ�˵�IP��ַ  ͨ�����Դ�����ʾ����

			char info[] = " is your outer IP .";   	

			webclient_data_len = strlen(ipAddr) ;	
			memcpy(webclient_data , ipAddr, webclient_data_len);
			memcpy(webclient_data + webclient_data_len, info, strlen(info));
			webclient_data_len += strlen(info);

			webclient_data_flag	= TRUE ;		
		}
	
		//�ر�����	
	}
	else {		   //  ����ҳ��δ�ҵ���Ӧ��IP��ַ
		u16		msglen = 0;

		msglen = len<(PARA_L_WEB*2)? len:(PARA_L_WEB*2);
		strcpy(EmailSubject,"IP isn't been found in the page.\r\n");
		memcpy(EmailMsg, data, msglen );
		EmailMsg[msglen] = '\0';

	}
	
	{//-----���Ƿ��ҵ�IP��ַ������EMAIL��
		uip_ipaddr_t *ipaddr ;
		char smtpSvr[PARA_L_WEB] ;
		getSmtpSvr(smtpSvr, parasets.emails[0].val);
		ipaddr = (uip_ipaddr_t *)LookupIP(smtpSvr);	

		if( ipaddr != NULL )	{  // DNS �Ѿ�������
			smtp_configure("ut.com", ipaddr);
			smtp_init();
			GetEmailUserPW();
			SendEmail_163(EmailSubject, EmailMsg);
		}
		webclient_close();
	}
}

//-----------------------------------
//   ��  Web ���ص���Ϣ�в���  ������ IP ��ַ�����ҷ��أ�
//-----------------------------------

char *ParsePageIpAddr(char *data, char *startStr, char *endStr )
{
//-----------------------------------
//   ����IP�ǣ�[218.13.182.108] 
//-----------------------------------
	int i = 0 , j=0 , lenD=0 ,lenS = 0, lenE = 0;
	static char ipaddr[20] ; 

	lenD = strlen(data);
	lenS = strlen(startStr);
	lenE = strlen(endStr);

	for( i=0; i<lenD ; i++) 
		if(memcmp((u8 *)data+i, (u8 *)startStr , lenS) == 0 ) 
			break;
   	for(j=0;j< lenD-i; j++) 
		if(memcmp((u8 *)data + i + lenS + j , endStr, lenE)==0) 
			break;
		//�ҵ�IP��ַ���ң� �Ѿ������пͻ����������£�
		//����Ϣ��ɸѡ��IP��ַ��ת����UNICODE���룬���͵�������ֻ���
	if(i<lenD && j<lenD ) {
		//���벻ͬ������ֱ��ת�����ֻ�������ת����UNICODE���룻
		memcpy(ipaddr , data + i + lenS , j ); 
		ipaddr[j] = '\0' ;
		return ipaddr;
	}
	else 
		return NULL;			
	
}


//--------------------------------------------------
//	 ��ȡ���������ĵ�ַ���˿ڡ�ת���� UNICODE���룬��ͨ��GSM���ŷ��ͳ�ȥ
//--------------------------------------------------
void AsciiIpPortToUncode(char *ip_port_ascii, char *ip_port_unicode)
{
		AsciiToUnicode(ip_port_ascii,ip_port_unicode);
}
//-------------------------------------------------
//��u8��ʽ��IP��ַ���˿ڣ�ת�����ַ���
//
//
//
//-------------------------------------------------
void IpU8ToStr(u8 *ip, u16 port, char *ip_port_str)
{
	u16		len = 0;
	u8		i =0;
	char	str[10];		

	for(i=0; i<PARA_L_IP ; i++)  {
		itoa(ip[i],str,10) ;

		memcpy(ip_port_str + len, str , strlen(str)) ; 
		len += strlen(str);

		memcpy(ip_port_str + len, "." , 1) ; 
		len ++;
	}

	itoa(port, str ,10) ;

	memcpy(ip_port_str + len, str , strlen(str)) ; 
	len += strlen(str);

	ip_port_str[len]=  '\0';

}
// ------------------------------------------------------------------
//  �������ƣ�    IpStrToU8
//
//  ���ַ����� IP��ַ"***.***.***.***" ת����4���ֽڸ�ʽ�ģ������سɹ����
//  ���ַǷ������1)�������֡�С���������������
//       		  2)��������4�ε�IP��ַ
//                3)ÿһ�γ���4λ
// 	return 
// ------------------------------------------------------------------
bool IpStrToU8(char *ipStr, u8 *ipaddr_1_to_4)
{
	int i = 0, j=0;
	char *ipaddr;
	unsigned char ip[4][4];

	ipaddr = ipStr;
	
	
	for(i=0; i< strlen(ipaddr); i++) 
		if(!IsDot(ipaddr[i]) && !Isdigit(ipaddr[i]))  //���������֡���.' ֮����������ţ���Ϊ�Ƿ�
			return FALSE;
	
	
	for(i=0; i< strlen(ipaddr); i++) 
		if(IsDot(ipaddr[i])) { 
			j++;
			if(j>3) return FALSE;  						//'.'����3��Ϊ�Ƿ���IP��ַ
		}
	

	ipaddr = ipStr;
	i=0;
	while(i<4) {									   // 4��IP��ַ
		for(j=0; j<3 ; j++) {
			if(IsDot(ipaddr[j]) || ipaddr[j]=='\0') 
				break;
			ip[i][j] = ipaddr[j];
			ip[i][j+1] = '\0';
		}
		if(j==3 && Isdigit(ipaddr[j])) return FALSE;   //IP ÿ���ֶγ���4λ�Ƿ�

		ipaddr += j+1;
		i++;
	}

	ipaddr_1_to_4[0] = AsciiToUnsignInt(ip[0]);
	ipaddr_1_to_4[1] = AsciiToUnsignInt(ip[1]);
	ipaddr_1_to_4[2] = AsciiToUnsignInt(ip[2]);
	ipaddr_1_to_4[3] = AsciiToUnsignInt(ip[3]);
	
	return TRUE;
}


/*
 * ��������IpU16ToStr
 * ����  ������������������ɵ�IP��ַ��ת�����ַ���
 * ����  ��ipaddr ���������ֽڵ�IP��ַ
 *         ��һ���ֽڣ�IP��ַ�����ֽ�
 *		   �ڶ����ֽڣ�IP��ַ�����ֽ�
 *		   ipString  ת����[***.***.***.***]��ʽ���ַ���
 * ����  ��������
 */

void IpU16ToStr(u16_t *ipaddr, char *ipString )
{
	int len = 0;

	ipString[0]=  '[';

	itoa(htons(ipaddr[0]) >> 8,ipString+1,10) ;
 	len = strlen(ipString);
	ipString[len]=  '.';

	itoa(htons(ipaddr[0]) & 0xff,ipString+len+1,10) ;
 	len = strlen(ipString);
	ipString[len]=  '.';

	itoa(htons(ipaddr[1]) >> 8,ipString+len+1,10) ;
 	len = strlen(ipString);
	ipString[len]=  '.';

	itoa(htons(ipaddr[1]) & 0xff,ipString+len+1,10) ;
 	len = strlen(ipString);
	ipString[len]=  ']';
	ipString[len+1]=  '\0';
}

bool IsDot(char c)
{
	if(c == 0x2E)
		return TRUE;
	else
		return FALSE;
}

bool Isdigit(char c)
{
	if((c >= 0x30) && (c <= 0x39))
		return TRUE;
	else
		return FALSE;
}

/*
 * ��������a_to_ui
 * ����  �����ַ���ת�����޷�������
 * ����  ���ַ���ָ��
 * ���  ������
 * ����  ������
 * ����  ��������
 */

u16 AsciiToUnsignInt (unsigned char s[])
{
    u8 result = 0;  

    while(*s>='0'&&*s<='9')  {
        result = result*10  + (*s-'0'),
		s++;  
    }

    return result;  	

}



void debug_info_show(char *info, u16_t len)
{
	if(WEBCLIENT_DEBUG)	{	//  ������ html��ҳ�ı���ʾ����
		webclient_data_len = len ;	
		memcpy(webclient_data , info , webclient_data_len);
		webclient_data_flag	= TRUE ;		
	}
}

//----------------
// ��IP��ַ����ΪUNICODE�룬��ӵ����Ͷ����У��绰�����Ѿ���UNICODE���룩
// ����Ϣ����GSM���Ͷ���
//----------------
void sendIP2phone(char *phone, char* ipaddr)
{

	ST_MSG    msg; 
	char unicode[UNICODE_SM_LEN/2];

	//���IP��....  ����� UNICODE ��
	AsciiToUnicode(ipaddr,unicode);
	memcpy(msg.sm, ACK_YOUIP, strlen(ACK_YOUIP));
	memcpy(msg.sm+strlen(ACK_YOUIP), unicode, strlen(unicode));
	msg.sm[strlen(ACK_YOUIP) + strlen(unicode)]= '\0' ;

	memcpy(msg.phone, phone, strlen(phone));
	msg.phone[strlen(phone)] = '\0';

	if(	! s_FIFO_Full()) 	 		//���Ͷ��в�����ѹ������
		s_FIFO_push(&msg) ;
}
//----------------
// ������������IP��ַ����ΪUNICODE�룬�˿ڱ����UNICODE�룬��ӵ����Ͷ����У��绰�����Ѿ���UNICODE���룩
// ����Ϣ����GSM���Ͷ���
//----------------
