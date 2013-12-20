struct partition_table {
	int offset;
	int size;
};
struct NCSD {
	char RSA2048[0x100];
	char magic_number[4];
	int size;
	long long media_id;
	long long FS_type;
	long long crypt_type;
	partition_table table[8];
	char SHA256[0x20];
	int header_size;
	int zero;
	long long partition_flags;
	long long id_table[8];
	char reserved[0x30];
};
struct NAND {
	NCSD Header;
	char Blank_1[0x12C00];
	char TWLN_partition[0x8FB5200];
	char Blank_2[0x49A00];
	char TWLP_partition[0x20B660];
	char Blank_3[0x1EE2FA0];
	char AGB_FIRM[0x30000];
	char FIRM0[0x400000];
	char FIRM1[0x400000];
	char CTR_NAND[0x1ECA00];
	char CTR_NAND_FAT16[0x2F3E3600];
};