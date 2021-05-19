#pragma once

#define RMDsize 160
#include <vector>
#include <string>

class RIPEMD160 {
private:
	char *message;
	std::vector<unsigned long>	MDbuf;	
	std::string					hashcode = std::string(RMDsize / 8, 0);	
	std::vector<unsigned long>	X;					
	unsigned int				i;					
	unsigned long				length;				
	unsigned long				nbytes;				

	unsigned unsigned long K[10] = {0x00000000, 0x5A827999, 0x6ED9EBA1, 0x8f1bbcdcUL, 0xA953FD4E, 0x00000000, 0x7A6D76E9, 0x6D703EF3, 0x5C4DD124, 0x50A28BE6}; // 0x50A28BE6, 0x5C4DD124, 0x6D703EF3, 0x7A6D76E9, 0x00000000


	unsigned long BYTES_TO_DWORD(char *strptr){
		return (((unsigned long) * ((strptr)+3) << 24) | ((unsigned long) * ((strptr)+2) << 16) | ((unsigned long) * ((strptr)+1) << 8) | ((unsigned long) * (strptr)));
}

	unsigned long ROL(unsigned long x, int n) {
		return (x << n) | (x >> (32 - n));
	}

	unsigned long F(unsigned long x, unsigned long y, unsigned long z) { return x ^ y ^ z; }		// ((x) ^ (y) ^ (z)) 
	unsigned long G(unsigned long x, unsigned long y, unsigned long z) { return x & y | ~x & z; }	// (((x) &(y)) | (~(x) & (z)))
	unsigned long H(unsigned long x, unsigned long y, unsigned long z) { return (((x) | ~(y)) ^ (z)); }		// (((x) | ~(y)) ^ (z))
	unsigned long I(unsigned long x, unsigned long y, unsigned long z) { return (((x) & (z)) | ((y) & ~(z)));	}   // (((x) &(z)) | ((y) & ~(z)))
	unsigned long J(unsigned long x, unsigned long y, unsigned long z) { return ((x) ^ ((y) | ~(z)));	}       // ((x) ^ ((y) | ~(z)))

	void FF(unsigned long &a, unsigned long b, unsigned long &c, unsigned long d, unsigned long e, unsigned long x, unsigned long s) {
		a += F(b, c, d) + x + K[0]; 
		a = ROL(a, s) + e; 
		c = ROL(c, 10); 
	}

	void GG(unsigned long &a, unsigned long b, unsigned long &c, unsigned long d, unsigned long e, unsigned long x, unsigned long s)        {
      (a) += G((b), (c), (d)) + (x) + K[1];
      (a) = ROL((a), (s)) + (e);
      (c) = ROL((c), 10);
	}

	void HH(unsigned long &a, unsigned long b, unsigned long &c, unsigned long d, unsigned long e, unsigned long x, unsigned long s) {
		(a) += H((b), (c), (d)) + (x) + K[2];
		(a) = ROL((a), (s)) + (e);
		(c) = ROL((c), 10);
	}

	void II(unsigned long &a, unsigned long b, unsigned long &c, unsigned long d, unsigned long e, unsigned long x, unsigned long s) {
		(a) += I((b), (c), (d)) + (x) + K[3];
		(a) = ROL((a), (s)) + (e);
		(c) = ROL((c), 10);
	}

	void JJ(unsigned long &a, unsigned long b, unsigned long &c, unsigned long d, unsigned long e, unsigned long x, unsigned long s) {
		(a) += J((b), (c), (d)) + (x) + K[4];
		(a) = ROL((a), (s)) + (e);
		(c) = ROL((c), 10);
	}

	void FFF(unsigned long &a, unsigned long b, unsigned long &c, unsigned long d, unsigned long e, unsigned long x, unsigned long s) {
		(a) += F((b), (c), (d)) + (x) + K[5];
		(a) = ROL((a), (s)) + (e);
		(c) = ROL((c), 10);
	}

	void GGG(unsigned long &a, unsigned long b, unsigned long &c, unsigned long d, unsigned long e, unsigned long x, unsigned long s) {
		(a) += G((b), (c), (d)) + (x) + K[6];
		(a) = ROL((a), (s)) + (e);
		(c) = ROL((c), 10);
	}

	void HHH(unsigned long &a, unsigned long b, unsigned long &c, unsigned long d, unsigned long e, unsigned long x, unsigned long s) {
		(a) += H((b), (c), (d)) + (x) + K[7];
		(a) = ROL((a), (s)) + (e);
		(c) = ROL((c), 10);
	}

	void III(unsigned long &a, unsigned long b, unsigned long &c, unsigned long d, unsigned long e, unsigned long x, unsigned long s) {
		(a) += I((b), (c), (d)) + (x) + K[8];
		(a) = ROL((a), (s)) + (e);
		(c) = ROL((c), 10);
	}

	void JJJ(unsigned long &a, unsigned long b, unsigned long &c, unsigned long d, unsigned long e, unsigned long x, unsigned long s) {
			(a) += J((b), (c), (d)) + (x)+0x50a28be6UL;
			(a) = ROL((a), (s)) + (e);
			(c) = ROL((c), 10);
	}

	void MDinit();

	void compress();

	void MDfinish(char *strptr);

public:
	RIPEMD160(char *message);
	
	std::string getHash();
};
