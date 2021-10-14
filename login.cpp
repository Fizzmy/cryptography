#include<cstdio>
#include<iostream>
#include<cstring> 
#define ui unsigned int
#define uc unsigned char
using namespace std;
char s[100010];
int n;
// S盒
static const int S[16][16] =
  { 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
	0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
	0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
	0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
	0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
	0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
	0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
	0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
	0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
	0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
	0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
	0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
	0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
	0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
	0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
	0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };
uc f[4][4],f1[4][4],f2[4][4],f3[4][4];
//列混合矩阵
static const int col[4][4] =
  { 2, 3, 1, 1,
	1, 2, 3, 1,
	1, 1, 2, 3,
	3, 1, 1, 2 };
uc key[20];
ui w[44];
uc nkey[4][4]; 
const int round=10;
//常量轮值表
static const int r[10] =
  { 0x01000000, 0x02000000,
    0x04000000, 0x08000000,
    0x10000000, 0x20000000,
    0x40000000, 0x80000000,
    0x1b000000, 0x36000000 };
ui g(ui x,int t)
{
	x=(x<<8)|(x>>24);
	ui y=0;
	y|=(S[(x>>28)][((x>>24)&15)]<<24);
	y|=(S[(x>>20)&15][(x>>16)&15]<<16);
	y|=(S[(x>>12)&15][(x>>8)&15]<<8);
	y|=(S[(x>>4)&15][(x>>0)&15]<<0);
	y^=r[t];
	return y;
}
int len=0;
char encode[40];
void print(int t)
{
	if (t<10) encode[len++]=t+'0';
	else encode[len++]='A'+t-10;
}
int GFMul2(int s) {
	int result = s << 1;
	int a7 = result & 0x00000100;
	if(a7 != 0) {
		result = result & 0x000000ff;
		result = result ^ 0x1b;
	}
	return result;
}

int GFMul3(int s) {
	return GFMul2(s) ^ s;
}

int GFMul4(int s) {
	return GFMul2(GFMul2(s));
}

int GFMul8(int s) {
	return GFMul2(GFMul4(s));
}

int GFMul9(int s) {
	return GFMul8(s) ^ s;
}

int GFMul11(int s) {
	return GFMul8(s) ^ GFMul2(s) ^ s;
}

int GFMul12(int s) {
	return GFMul8(s) ^ GFMul4(s);
}

int GFMul13(int s) {
	return GFMul8(s) ^ GFMul4(s) ^ s;
}

int GFMul14(int s) {
	return GFMul8(s) ^ GFMul4(s) ^ GFMul2(s);
}

//GF上的二元运算
int GFMul(int n, int s) {
	int result;

	if(n == 1)
		result = s;
	else if(n == 2)
		result = GFMul2(s);
	else if(n == 3)
		result = GFMul3(s);
	else if(n == 0x9)
		result = GFMul9(s);
	else if(n == 0xb)//11
		result = GFMul11(s);
	else if(n == 0xd)//13
		result = GFMul13(s);
	else if(n == 0xe)//14
		result = GFMul14(s);

	return result;
}
char ans[40];
int main()
{
	freopen("word.txt","r",stdin);
	char c;
	while ((c=getchar())!=EOF)
		s[n++]=c;
	fclose(stdin);
	freopen("password_encode.txt","r",stdin);
	scanf("%s",ans);
	fclose(stdin);
	freopen("CON","r",stdin);
	while (1)
	{
		len=0;
		printf("请输入密码(16位以内)：\n");
		scanf("%s",key);
		for (int j=0;j<4;j++)
			for (int i=0;i<4;i++)
				w[j]=(w[j]<<8)|key[j*4+i];
		//求轮密钥 
		for (int i=4;i<44;i++)
		{
			if (i%4==0)
				w[i]=g(w[i-1],i/4-1)^w[i-4];
			else w[i]=w[i-1]^w[i-4];
		}
		for (int i=0;i<n;i+=16)
		{
			
			//取128位 
			for (int j=0;j<16;j++)
				f[j%4][j/4]=s[i+j];
			
			//初始XOR轮密钥 
			for (int x=0;x<4;x++)
				for (int y=0;y<4;y++)
					f[x][y]^=key[y*4+x];
			
			for (int T=1;T<round;T++)
			{
				//S盒转换 
				for (int x=0;x<4;x++)
					for (int y=0;y<4;y++)
						f1[x][y]=S[(f[x][y]>>4)][f[x][y]&(15)];
			
				//行移位 
				for (int x=0;x<4;x++)
					for (int y=0;y<4;y++)
						f2[x][y]=f1[x][(y+x)%4];
				//列混合
				for (int x=0;x<4;x++)
					for (int y=0;y<4;y++)
					{
						f3[x][y]=0;
						for (int z=0;z<4;z++)
							f3[x][y]^=GFMul(col[x][z],f2[z][y]);
					}
				//取出轮密钥 
				for (int y=0;y<4;y++)
				{
					nkey[0][y]=((w[T*4+y]>>24)&255);
					nkey[1][y]=((w[T*4+y]>>16)&255);
					nkey[2][y]=((w[T*4+y]>>8)&255);
					nkey[3][y]=((w[T*4+y]>>0)&255);
				}
				//xor轮密钥
				for (int x=0;x<4;x++)
					for (int y=0;y<4;y++)
						f[x][y]=f3[x][y]^nkey[x][y];
			}
			
			//最后一轮没有列混合 
			//S盒转换 
			for (int x=0;x<4;x++)
				for (int y=0;y<4;y++)
					f1[x][y]=S[(f[x][y]>>4)][f[x][y]&(15)];
			//行移位 
			for (int x=0;x<4;x++)
				for (int y=0;y<4;y++)
					f2[x][y]=f1[x][(y+x)%4];
			//取出轮密钥 
			for (int y=0;y<4;y++)
			{
				nkey[0][y]=((w[40+y]>>24)&255);
				nkey[1][y]=((w[40+y]>>16)&255);
				nkey[2][y]=((w[40+y]>>8)&255);
				nkey[3][y]=((w[40+y]>>0)&255);
			}
			//xor轮密钥
			for (int x=0;x<4;x++)
				for (int y=0;y<4;y++)
					f[x][y]=f2[x][y]^nkey[x][y];
	
			for (int x=0;x<4;x++)
				for (int y=0;y<4;y++)
				{
					print(f[y][x]>>4);
					print(f[y][x]&15);
				}
		}
		if (strcmp(ans,encode)==0)
		{
			printf("密码正确！\n");
			break;
		}
		else printf("密码错误！\n");
	}
}

