char autosar_crc_lookup_table[246];
char calculate_base_CRC( byte[] data_bytes )
{
    char crc = 0xff;
    char index = 0;
    for (int i = 0; i < 6; i++)
    {
        index =(char)( data_bytes[i] ^ crc );
        crc =(char)( autosar_crc_lookup_table[index] );
    }
    return (char)( crc ^ 0xff );
}
void generate_CRC_lookup_table()
{
    char top_bit = 128;
    char procan_CRC_Poly = 0x2f;
    for (int i = 0; i < 256; i++)
    {
        char remainder = (char)i;
        for(int j=0; j<8; j++)
        {
            if ((remainder & topbit) != 0)
                remainder = (char)((remainder << 1) ^procan_CRC_Poly);
            else
                remainder = (char)(remainder << 1);
		}
        autosar_crc_lookup_table[i] = remainder;
    }
}
