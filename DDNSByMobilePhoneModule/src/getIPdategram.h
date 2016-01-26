/*

http://20140507.ip138.com/ic.asp
用socket 往 219.153.49.149 发送下面数据

---------------------------------------
客户端请求报文（文本格式）：
html.h
GET /ic.asp HTTP/1.1
Accept: image/jpeg, application/x-ms-application, image/gif, application/xaml+xml, image/pjpeg, application/x-ms-xbap, application/msword, application/vnd.ms-excel, application/vnd.ms-powerpoint, 
Accept-Language: zh-CN
User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.1; Trident/4.0; SLCC2; .NET CLR 2.0.50727; .NET CLR 3.5.30729; .NET CLR 3.0.30729; Media Center PC 6.0; .NET4.0C; .NET4.0E; Tablet PC 2.0)
Accept-Encoding: gzip, deflate
Host: 20140507.ip138.com
Connection: Keep-Alive
Cookie: ASPSESSIONIDACBBQCSA=FFEFDKCACBLOJGIBILFBIFCC; ASPSESSIONIDCCCDSBTB=LCKACKCALAMNPMLBGPJIIIAB; ASPSESSIONIDACABQDTB=ACMACKCALLKHLIEOIGAGBNNO; ASPSESSIONIDAAABRDTB=MLBHCKCAKECDFDNEHMJKHHCC


----------------------
服务器响应：
HTTP/1.1 200 OK
Date: Thu, 28 Aug 2014 05:58:53 GMT
Server: Microsoft-IIS/6.0
X-Powered-By: ASP.NET
Content-Length: 230
Content-Type: text/html
Set-Cookie: ASPSESSIONIDCQRRDCBQ=FOKDLKBBFHPFJNBHGPGENKHG; path=/
Cache-control: private

<html>
<head>
<meta http-equiv="content-type" content="text/html; charset=gb2312">
<title> 您的IP地址 </title>
</head>
<body style="margin:0px"><center>您的IP是：[218.13.182.108] 来自：广东省珠海市 电信</center></body></html>

	   
*/

/*  ------------------------------------------------------------
网站：ip.cn 	地址： 211.155.86.186

请求报文：
GET / HTTP/1.1
Accept:image/gif, image/jpeg, image/pjpeg, image/pjpeg, application/x-shockwave-flash, application/x-ms-application, application/x-ms-xbap, application/vnd.ms-xpsdocument, application/xaml+xml, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, 
Accept-Encoding:gzip, deflate
Accept-Language:zh-cn
Connection:Keep-Alive
Host:ip.cn
User-Agent:Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 2.0.50727; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; InfoPath.2)


服务器回复：
GET / HTTP/1.1
Accept: image/gif, image/jpeg, image/pjpeg, image/pjpeg, application/x-shockwave-flash, application/x-ms-application, application/x-ms-xbap, application/vnd.ms-xpsdocument, application/xaml+xml, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, 
Accept-Language: zh-cn
User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 2.0.50727; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; InfoPath.2)
Accept-Encoding: gzip, deflate
Host: ip.cn
Connection: Keep-Alive
  还有下面二进制数据：
37 31 36 0D 0A 

1F 8B 08 00 00 00 00 00 00 03 ED 57 5B 6F DB D6 1D 7F 96 3F C5 29 1F 26 19 30 0F 45 DD 2C 
DB A2 1E 6A 7B 81 B1 22 D3 30 EF 61 08 82 E2 88 3C 92 4E 42 91 2C 0F 29 45 4D 02 38 45 B7 
26 4D 82 34 F5 D6 61 81 B3 24 43 B3 A1 DD 16 67 C3 D2 B8 49 55 03 FB 2A D5 CD 4F FD 0A FB 
1F 52 A4 28 39 DE E5 61 6F 33 20 93 E7 7F 7E FF FB E5 1C 56 DE DA FA F1 E6 EE CF 6B DB A8 
E5 B5 CD EA 52 25 7A 50 62 C0 A3 4D 3D 02 3B 9E 23 D3 F7 7C D6 D1 A4 4D DB F2 A8 E5 C9 BB 
3D 87 4A 48 0F 57 9A E4 D1 2B 9E 22 58 37 90 DE 22 2E A7 9E E6 7B 0D B9 2C 81 0C 8F 79 26 
AD EE D4 B0 6E 21 19 ED D4 D0 F0 E0 F9 F0 E1 DE E8 D1 D3 C9 E1 EF D1 35 B1 1C 7F F2 CB 41 
FF EE B8 FF 0C 96 A3 5B B7 47 07 AF 86 FD 4F 87 7F FD 1D 6C 55 94 90 7F 6A 8B 45 DA 54 93 
5C BB 6E 7B 3C A1 9F 98 A6 84 94 79 D0 8F 68 AF 6B BB 46 12 B6 53 5B D9 A9 85 8A 57 46 07 
7F 06 3D 40 19 7E FE D9 B8 7F 3F D8 4A 5A B6 92 B4 2B E2 09 6D BB F7 72 25 B6 4F 9A 57 BA 
45 B9 EE 32 C7 63 B6 95 D0 3B 38 DA 1F 1C 3D 58 F4 FD BB BD 1B A7 75 00 71 FC B7 6F C7 4F 
9E 09 F4 E8 D7 CF 47 77 9F 0D 5F ED 03 35 D6 1D AB 9E 31 FC EA C5 E4 F0 21 6C 8D 1F DF 38 
79 FD E1 C9 93 17 E1 D6 F7 DF DC 19 DE 3B 84 F7 E1 D7 C7 C3 FB 1F 03 F2 E4 CB 07 A3 5B CF 
85 E2 E3 3F 9D EC 7D 2A 28 FB 5F 4D 9E DC 81 97 C1 F1 C3 93 DF 7E 21 14 DD 3C 06 E1 83 57 
7F 14 C4 A3 BF 0C 5E DF 0E E5 7F B7 F7 81 70 D6 64 D6 65 D4 72 69 43 4B 8B C2 58 57 14 8E 
99 23 EB 86 85 75 BB AD E8 9C 2B 75 1B B2 E3 B9 C4 C1 6D 06 54 CE D3 C8 A5 A6 96 E6 5E CF 
A4 BC 45 A9 97 46 1E 14 90 96 0E EA 46 00 E6 A3 D8 61 B4 EB D8 AE 97 08 61 97 19 5E 4B 33 
68 87 E9 54 0E 16 2B 08 A4 B3 B6 DF 96 B9 4E 4C AA 65 71 71 21 19 0D DB 6D 13 4F 36 A8 47 
F5 85 8C 78 D4 A4 4E CB B6 A8 66 D9 82 EB 2D 59 BE C0 1A C8 F4 D0 CE 36 2A 5F 04 4A 98 47 
C4 5D 5D 93 CE 72 F4 12 57 18 2D E3 4B 5C AA 56 94 90 41 C8 BA 40 2D 83 35 2E CA F2 7F 16 
AE 36 F9 2F A2 A4 4C 3B B3 6E 1B 3D 64 5B EF D8 C4 D0 24 C3 D6 FD 36 F8 85 1B 42 38 6E C0 
92 67 96 85 5F 06 EB 20 DD 24 9C 6B 92 F0 1D 34 51 57 6E 98 3E 33 60 37 95 DC 16 72 A9 2B 
A8 A9 0A 09 2D 96 14 F0 8B B5 9B 67 07 01 36 15 D3 6E DA B8 C9 1A 22 06 44 08 55 40 6A 75 
69 5E BA F0 B1 4E A6 E2 7D 33 22 5B A4 03 B9 EA C8 0E 33 4D 8E 74 70 01 CC 0B 16 01 32 05 
E1 8B A0 04 52 D8 A1 A0 24 61 9C 68 91 A0 D2 85 E6 8A 62 B2 88 69 86 32 EA D8 69 39 52 35 
6C 9F 85 66 89 FB EB 5F F0 5B 1C 8B C1 26 55 B7 CE FF F4 6C D8 7B EE 14 35 78 75 67 FC FA 
EF 20 3B 89 AD 28 BE 79 56 64 38 25 AE DE 12 A5 1A 06 47 BC 45 F5 0B B3 8B 04 95 AB 49 CC 
32 E8 95 C0 15 04 15 DE B2 21 EB E7 B6 77 A5 48 8A E0 92 43 51 D3 C8 31 CB F1 BD A9 20 06 
5C 41 29 05 83 5A 42 8E 49 74 DA B2 4D 48 B8 26 4D 0E 5F 4E BE DD 1F FE E2 E9 E4 0F 37 C2 
68 8E 1F 7C 38 7C F4 68 F8 C9 DD D1 CD CF 66 43 2B D6 C5 1D 62 E5 E7 B4 30 B0 86 47 2A B8 
5F 6F 33 2F 46 D7 3D 0B C1 4F 76 5C D6 26 6E 4F 42 1D 62 FA 00 0B 55 85 3E 2B C2 FC 59 80 
52 D3 08 09 B1 2E E5 BE E9 41 DA 13 21 EB 52 18 F7 D5 8A 53 1D F6 F7 87 B7 EE 82 89 DF 7F 
F3 A0 A2 DB 06 AD E6 D4 32 56 F3 58 2D E7 B0 9A 2D 57 94 80 F8 03 AB CE 9D 8D D1 C3 A7 93 
8F BE 04 24 4C C3 C1 D1 C1 F8 E0 C6 F8 DE E3 D1 8B 97 C3 A3 0F 10 14 C5 E0 F8 49 45 71 84 
D4 73 D4 DE A9 AD A3 73 3E B1 9A EF B7 6C 7F 25 7C 35 6C AB B9 82 36 5B CC 22 01 30 B0 75 
2E A5 B3 A9 41 78 CF D2 C3 B6 51 14 87 34 A1 B7 72 B8 69 DB 4D E8 EC 1E 0C 07 9D 88 AC 06 
2D 14 EE 8A 51 42 0C 5E EF 85 A0 C5 91 C2 2C 1E F7 C1 0C 25 2D 21 F1 17 0C 0C A8 54 C6 21 
AF BD 75 66 C1 CC A1 72 DD B4 F5 CB 1B C1 A4 5C CF E7 4B CE 95 8D 16 65 CD 96 B7 9E 2B 67 
9D 2B 53 56 83 78 44 26 86 AC 9B 2C 18 8B 3A 91 1D BF 2E E7 0B 65 55 5D 2D 94 0B C5 E2 6A 
B9 94 2F 2D A0 B9 69 03 B6 90 2F AA 85 42 39 9F 55 85 A9 60 61 EC 7E 75 29 93 B0 12 69 A8 
0B D5 6B 77 71 92 78 ED 1A BA 70 71 19 3B 3E 6F 65 AE 5E 5F DE 58 9A 79 BB D0 27 A2 0A 0C 
DF E6 2D 3F 9A D4 68 2B 5C A2 4D BB 2D C6 1E 7A 7B FB DC CE 79 24 E6 6D 6A AE B7 0C 2E 7B 
D0 9F C4 90 42 DB C3 85 7C 99 F6 34 69 BE 52 22 80 B8 6B 9C B1 E7 BB A6 26 49 51 C6 A3 4C 
CF DA 4A B9 44 3A 24 A4 82 9D 1D E2 A2 A9 D5 3F F1 A9 DB 83 28 5C E5 2D 38 D3 DE 15 2D B9 
0E 2D A9 5B D2 F5 8D A5 54 A6 E1 5B 41 8F 67 96 D1 55 B0 3F 60 E4 00 8F 87 BA 0E 46 7B 74 
DB A4 62 95 49 87 2A D2 10 B2 54 CA E0 58 18 00 E8 F4 82 09 E9 0D D8 0B CB 50 43 9E EB D3 
29 1C 6A 52 A0 A3 61 EE 41 21 EA 78 6A 68 50 8F B4 5D A7 06 D4 5F 7A CA 30 BD CF 09 A6 9F 
ED FE 50 2E 07 F4 4C 6C 5C 93 7A 53 CB F8 DB BD 5D D2 3C 0F DE 65 D2 E2 30 49 2F 5F C8 5E 
14 79 FE 37 58 71 92 05 D8 65 4C 1C 07 8E 4E 68 31 D3 C8 18 5C 78 78 7D 39 33 57 1B 6F 4C 
FF F6 F9 AD 30 F9 A7 0B C7 85 C6 A5 D2 62 5D C0 75 C1 85 26 15 FF 65 66 35 EC 70 98 8D 0E 
F6 26 C7 F7 C3 B9 B4 8E E2 D1 0E C7 DD 6A 16 97 D7 A0 22 E0 57 CA 4D 07 FD 1C 4D 0C FB 39 
0E 35 A7 E2 7C 01 17 8A 78 6D 75 CA 90 24 BD 01 0F E4 02 5E 2D E0 6C 0C 8F 29 A7 D1 50 9C 
B9 42 01 97 8A 58 8D EC 99 A3 BD 81 03 C8 6B 58 14 76 AC 20 41 3A 8D C7 6A B1 04 7B 2A CE 
E5 63 0D 49 DA 69 8E 72 16 AF 95 71 BE 8C 73 B9 72 C4 91 A4 9D E2 28 81 C0 52 09 7E 60 47 
64 D4 1C ED 14 C7 2A 50 21 84 2A 00 8A 6A 94 87 24 ED 0D 7E 97 70 31 07 EA C1 F0 9C 1A 7B 
9E 24 06 3C A9 F8 EC F9 FF 44 FF DF 4D F4 D4 FC D5 A7 01 DF 09 D1 95 D3 A9 FE E3 8B 5C 36 
5B 92 73 59 B5 80 C2 AF C5 93 DF F4 77 36 6B C3 CF 3F 52 F3 D9 6C AE 58 28 C0 AD 4D 5E 13 
87 6F C8 11 27 7A 3A CD BA DD 2E 2E AA CC 21 22 0D 70 1D 21 2E 4C 1C 4D 7A B7 6E 12 EB B2 
54 65 35 62 AC 20 56 13 D7 FE 49 FF 70 F0 FA AB D1 D1 D1 E8 E6 BD C1 D1 ED 49 BF 3F 5F 3A 
09 89 9E EE 50 A3 49 83 D4 4A D5 5D 30 E8 E3 C7 27 7B 8F C2 FB 9D 33 73 2E 7E 88 81 16 DC 
D4 83 4F E9 7F 02 15 19 C4 65 62 0F 00 00 0D 0A 30 0D 0A 0D 0A 

----------------------------------------------------------------
*/

/*  ------------------------------------------------------------
网站：http://ip.qq.com/ 	地址： 183.66.3.174	,218.13.182.108

GET / HTTP/1.1
Host:ip.qq.com

请求报文：
GET / HTTP/1.1
Accept:image/gif, image/jpeg, image/pjpeg, image/pjpeg, application/x-shockwave-flash, application/x-ms-application, application/x-ms-xbap, application/vnd.ms-xpsdocument, application/xaml+xml, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, 
Accept-Encoding:gzip, deflate
Accept-Language:zh-cn
Connection:Keep-Alive
Cookie:ac=1,030,001; pt2gguin=o2109309227; ptcz=101537c815368bcacece004fe0b947ead103b140670748b117cb03f2f543daf2; pgv_pvid=5833584650; o_cookie=2109309227; ptui_loginuin=zhiyuchen2014@qq.com; pgv_info=ssid=s5604103685; ipqqcom_user_id=721036
Host:ip.qq.com
User-Agent:Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 2.0.50727; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; InfoPath.2)


服务器回复：
HTTP/1.1 200 OK
Date: Thu, 25 Sep 2014 08:26:33 GMT
Server: Apache/2.4.2 (Unix)
Cache-Control: max-age=0, must-revalidate
Content-Encoding: gzip
Keep-Alive: timeout=15, max=100
Connection: Keep-Alive
Transfer-Encoding: chunked
Content-Type: text/html



----------------------------------------------------------------
*/

#define GSM_CMD_TO			"0054004F003A"				//"TO:" UNICODE编码
#define GSM_CMD_GETIP		"00670065007400690070"		//"getip" UNICODE编码   
#define GSM_CMD_HELP		"00680065006C0070"			//"help" UNICODE编码 
#define GSM_CMD_GETHOST		"0067006500740068006F00730074"//"gethost" UNICODE编码   

#define	GSM_INFO_HOST		"00720065006D006F0074006500200068006F00730074003A"  //反馈给短信的 remote host UNICODE 编码


#define ACK_REMORTIP		"914D7F6E4E3B673A662FFF1A"  //"配置主机是：" 
#define ACK_YOUIP			"60A8768400490050662FFF1A"  //"您的IP是：" 
#define ACK_WAITING			"8BF77A0D540E002E002E002E002E002E002E"  //请稍后...... 
#define ACK_REQ_ERR			"95198BEFFF1A8BF76C4276847F517AD96CA1670954CD5E943002"  //错误：请求的网站没有响应。

#define HELP_AMOUNT			4							//帮助总条数

char	ack_help[HELP_AMOUNT][86]= { 
		"00680065006C0070003A5E2E52A9000A",							/*//\"help\" UNICODE编码 */
		"00670065007400690070003A83B753D65F53524D00490050000A",		/*//\"getip\" UNICODE编码  */
		"0054004F003A75358BDD53F77801002C4FE1606F00208F6C53D14FE1606F523067D053F77801000A",	/*//"TO:" UNICODE编码*/
		"0067006500740068006F00730074"	//gethost
};

//-----------------------------------------------------------------------------------------
// request_frame_web1
/***********************
GET /ic.asp HTTP/1.1
Host: 20140507.ip138.com
***********************/

/*
www.baidu.com


GET / HTTP/1.1
Accept: image/gif, image/jpeg, image/pjpeg, image/pjpeg, application/x-shockwave-flash, application/x-ms-application, application/x-ms-xbap, application/vnd.ms-xpsdocument, application/xaml+xml, application/vnd.ms-excel, application/vnd.ms-powerpoint, application/msword, 
Accept-Language: zh-cn
User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 5.1; Trident/4.0; .NET CLR 2.0.50727; .NET CLR 3.0.4506.2152; .NET CLR 3.5.30729; InfoPath.2)
Accept-Encoding: gzip, deflate
Host: www.baidu.com
Connection: Keep-Alive
Cookie: BD_UPN=1123314151; H_PS_BBANNER=3; H_PS_645EC=a9e2fowJgo2i9t2GN%2F6j8%2BETOaH2GPFp2zisG72akBOaZ5nvfehBRDCj0kQ; BAIDUID=0AE3424B61EA7B56007DE2ED7D265451:FG=1; BAIDUPSID=3F4755FBEFED9DB977EA262E3C7A7AC4


*/


