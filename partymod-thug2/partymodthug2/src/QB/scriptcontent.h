
/* calculate checksum from script without function name (:i function $<name>$) */


/*
const uint8_t enter_kb_chat_new[] = {
	0x01, 0x16, 0xDF, 0x01, 0xA8, 0xBF, 0x16, 0xCA, 0xAF, 0xCF, 0x7B, 0x07, 0x17, 0x12, 0x02, 0x00,
	0x00, 0x01, 0x16, 0x54, 0x52, 0x42, 0xF0, 0x16, 0x85, 0xD2, 0xCE, 0xB1, 0x16, 0x9D, 0x56, 0xB7,
	0x02, 0x16, 0x53, 0x19, 0x26, 0x7F, 0x07, 0x1F, 0x00, 0x00, 0xA0, 0x43, 0x00, 0x00, 0x82, 0x43,
	0x16, 0x7F, 0xD4, 0xB7, 0x5D, 0x07, 0x16, 0x0B, 0x85, 0x4C, 0x5D, 0x16, 0x79, 0xB5, 0x1E, 0x4F,
	0x07, 0x1B, 0x10, 0x00, 0x00, 0x00, 0x45, 0x4E, 0x5A, 0x45, 0x52, 0x20, 0x4D, 0x45, 0x53, 0x53,
	0x41, 0x47, 0x45, 0x3A, 0x20, 0x00, 0x16, 0x78, 0xCE, 0x92, 0xA5, 0x07, 0x1B, 0x0E, 0x00, 0x00,
	0x00, 0x45, 0x4E, 0x54, 0x45, 0x52, 0x20, 0x4D, 0x45, 0x53, 0x53, 0x41, 0x47, 0x45, 0x00, 0x16,
	0x70, 0x3B, 0xEF, 0x68, 0x07, 0x17, 0x01, 0x00, 0x00, 0x00, 0x16, 0xC4, 0xA1, 0xE3, 0x69, 0x07,
	0x17, 0x00, 0x02, 0x00, 0x00, 0x16, 0x80, 0xD2, 0x50, 0x2A, 0x01, 0x16, 0xDF, 0x01, 0xA8, 0xBF,
	0x16, 0xCA, 0xAF, 0xCF, 0x7B, 0x07, 0x17, 0x68, 0x01, 0x00, 0x00, 0x01, 0x24, 0x01
};
*/
const uint8_t enter_kb_chat_new[] = {
0x01, 0x16, 0xDF, 0x01, 0xA8, 0xBF, 0x16, 0xCA, 0xAF, 0xCF, 0x7B, 0x07, 0x17, 0x12, 0x02, 0x00, 0x00, 0x01, 0x16, 0x54, 0x52, 0x42, 0xF0, 0x16, 0x85, 0xD2, 0xCE, 0xB1, 0x16, 0x9D, 0x56, 0xB7, 0x02, 0x16, 0x53, 0x19, 0x26, 0x7F, 0x07, 0x1F, 0x00, 0x00, 0xA0, 0x43, 0x00, 0x00, 0x82, 0x43, 0x16, 0x7F, 0xD4, 0xB7, 0x5D, 0x07, 0x16, 0x0B, 0x85, 0x4C, 0x5D, 0x16, 0x79, 0xB5, 0x1E, 0x4F, 0x07, 0x1B, 0x10, 0x00, 0x00, 0x00, 0x41, 0x41, 0x54, 0x45, 0x52, 0x20, 0x4D, 0x45, 0x53, 0x53, 0x41, 0x47, 0x45, 0x3A, 0x20, 0x00, 0x16, 0x78, 0xCE, 0x92, 0xA5, 0x07, 0x1B, 0x0E, 0x00, 0x00, 0x00, 0x45, 0x4E, 0x54, 0x45, 0x52, 0x20, 0x4D, 0x45, 0x53, 0x53, 0x41, 0x47, 0x45, 0x00, 0x16, 0x70, 0x3B, 0xEF, 0x68, 0x07, 0x17, 0x01, 0x00, 0x00, 0x00, 0x16, 0xC4, 0xA1, 0xE3, 0x69, 0x07, 0x17, 0x00, 0x02, 0x00, 0x00, 0x16, 0x80, 0xD2, 0x50, 0x2A, 0x01, 0x16, 0xDF, 0x01, 0xA8, 0xBF, 0x16, 0xCA, 0xAF, 0xCF, 0x7B, 0x07, 0x17, 0x68, 0x01, 0x00, 0x00, 0x01, 0x24, 0x01 };


const uint8_t enablesun_new[] = {
0x01, 0x16, 0xDF, 0x01, 0xA8, 0xBF, 0x16, 0xEC, 0x4C, 0x4F, 0x20, 0x07, 0x17, 0x01, 0x00, 0x00, 0x00, 0x01, 0x16, 0xE8, 0x46, 0x5C, 0x16, 0x01, 0x16, 0x6C, 0x7D, 0x14, 0x5A, 0x16, 0x95, 0xDB, 0x3F, 0x08, 0x07, 0x1A, 0x00, 0x40, 0x05, 0x45, 0x01, 0x24, 0x01
};

const uint8_t scalingmenu_get_limits_original[] = {
	0x01, 0x16, 0x31, 0xBE, 0x5C, 0xD0, 0x01, 0x16, 0xF4, 0xB1, 0x74, 0x6D, 0x16, 0x9A, 0x85, 0xE6,
	0x67, 0x07, 0x2D, 0x16, 0x6B, 0x47, 0x64, 0x3C, 0x01, 0x16, 0xB0, 0xC4, 0xB5, 0x39, 0x16, 0xB6,
	0xFE, 0x12, 0x52, 0x01, 0x2D, 0x16, 0xFE, 0x98, 0x8C, 0x7F, 0x07, 0x17, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x20, 0x01, 0x47, 0xC8, 0x00, 0x16, 0x9C, 0xDE, 0x0C, 0x94, 0x16, 0xBC, 0x41, 0x48, 0x17,
	0x07, 0x0E, 0x0E, 0x16, 0xB6, 0xFE, 0x12, 0x52, 0x05, 0x2D, 0x16, 0xFE, 0x98, 0x8C, 0x7F, 0x06,
	0x0F, 0x08, 0x16, 0x39, 0x8F, 0xF0, 0xB6, 0x0F, 0x16, 0x06, 0x10, 0x41, 0x8E, 0x07, 0x2D, 0x16,
	0x39, 0x8F, 0xF0, 0xB6, 0x01, 0x47, 0x52, 0x00, 0x0E, 0x2D, 0x16, 0x77, 0x31, 0x81, 0x3F, 0x07,
	0x17, 0x01, 0x00, 0x00, 0x00, 0x0F, 0x01, 0x2D, 0x16, 0x2F, 0xE2, 0x84, 0x5E, 0x07, 0x0E, 0x0E,
	0x16, 0xB6, 0xFE, 0x12, 0x52, 0x05, 0x2D, 0x16, 0xFE, 0x98, 0x8C, 0x7F, 0x06, 0x0F, 0x08, 0x16,
	0x87, 0x3E, 0x42, 0x1F, 0x0F, 0x01, 0x2D, 0x16, 0x76, 0xDD, 0x89, 0x62, 0x07, 0x0E, 0x0E, 0x16,
	0xB6, 0xFE, 0x12, 0x52, 0x05, 0x2D, 0x16, 0xFE, 0x98, 0x8C, 0x7F, 0x06, 0x0F, 0x08, 0x16, 0xDE,
	0x01, 0x4F, 0x23, 0x0F, 0x01, 0x48, 0x42, 0x00, 0x01, 0x2D, 0x16, 0x2F, 0xE2, 0x84, 0x5E, 0x07,
	0x0E, 0x0E, 0x16, 0xB6, 0xFE, 0x12, 0x52, 0x05, 0x2D, 0x16, 0xFE, 0x98, 0x8C, 0x7F, 0x06, 0x0F,
	0x08, 0x16, 0x44, 0x39, 0xE7, 0x53, 0x0F, 0x01, 0x2D, 0x16, 0x76, 0xDD, 0x89, 0x62, 0x07, 0x0E,
	0x0E, 0x16, 0xB6, 0xFE, 0x12, 0x52, 0x05, 0x2D, 0x16, 0xFE, 0x98, 0x8C, 0x7F, 0x06, 0x0F, 0x08,
	0x16, 0x1D, 0x06, 0xEA, 0x6F, 0x0F, 0x01, 0x28, 0x01, 0x22, 0x01, 0x28, 0x01, 0x2D, 0x16, 0xFE,
	0x98, 0x8C, 0x7F, 0x07, 0x0E, 0x2D, 0x16, 0xFE, 0x98, 0x8C, 0x7F, 0x0B, 0x17, 0x01, 0x00, 0x00,
	0x00, 0x0F, 0x01, 0x21, 0x2D, 0x16, 0x4D, 0x3D, 0x5B, 0x7F, 0x01, 0x47, 0x1C, 0x00, 0x39, 0x16,
	0x7B, 0x71, 0x66, 0xCF, 0x16, 0x2F, 0xE2, 0x84, 0x5E, 0x01, 0x2D, 0x16, 0x2F, 0xE2, 0x84, 0x5E,
	0x07, 0x1A, 0x00, 0x00, 0xB4, 0x42, 0x01, 0x28, 0x01, 0x47, 0x1C, 0x00, 0x39, 0x16, 0x7B, 0x71,
	0x66, 0xCF, 0x16, 0x76, 0xDD, 0x89, 0x62, 0x01, 0x2D, 0x16, 0x76, 0xDD, 0x89, 0x62, 0x07, 0x1A,
	0x00, 0x00, 0x16, 0x43, 0x01, 0x28, 0x01, 0x29, 0x16, 0x2F, 0xE2, 0x84, 0x5E, 0x07, 0x2D, 0x16,
	0x2F, 0xE2, 0x84, 0x5E, 0x16, 0x76, 0xDD, 0x89, 0x62, 0x07, 0x2D, 0x16, 0x76, 0xDD, 0x89, 0x62,
	0x01, 0x24, 0x01
};

const uint8_t scalingmenu_get_limits_addition[] = {
	0x01, 0x2D, 0x16, 0x2F, 0xE2, 0x84, 0x5E, 0x07, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x01, 0x2D, 0x16,
	0x76, 0xDD, 0x89, 0x62, 0x07, 0x1A, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x29, 0x16, 0x2F, 0xE2, 0x84,
	0x5E, 0x07, 0x2D, 0x16, 0x2F, 0xE2, 0x84, 0x5E, 0x16, 0x76, 0xDD, 0x89, 0x62, 0x07, 0x2D, 0x16,
	0x76, 0xDD, 0x89, 0x62, 0x01, 0x24, 0x01
};

/*
* 
* original:
* 
:i function $scalingmenu_get_limits$
	:i $GetCurrentSkaterProfileIndex$
	:i $GetSkaterProfileInfo$$player$ = %GLOBAL%$currentSkaterProfileIndex$
	:i $GetArraySize$$scalingmenu_constraints$
	:i %GLOBAL%$index$ = %i(0,00000000)
	:i while

		:i if $ChecksumEquals$$a$ =  ( ($scalingmenu_constraints$:a{%GLOBAL%$index$:a}) ->$part$) $b$ = %GLOBAL%$part$
			:i if  (%GLOBAL%$is_male$ = %i(1,00000001))
				:i %GLOBAL%$min$ =  ( ($scalingmenu_constraints$:a{%GLOBAL%$index$:a}) ->$male_min$)
				:i %GLOBAL%$max$ =  ( ($scalingmenu_constraints$:a{%GLOBAL%$index$:a}) ->$male_max$)
			:i else
				:i %GLOBAL%$min$ =  ( ($scalingmenu_constraints$:a{%GLOBAL%$index$:a}) ->$female_min$)
				:i %GLOBAL%$max$ =  ( ($scalingmenu_constraints$:a{%GLOBAL%$index$:a}) ->$female_max$)
			:i endif
			:i continue

		:i endif
		:i %GLOBAL%$index$ =  (%GLOBAL%$index$ + %i(1,00000001))
	:i loop_to %GLOBAL%$array_size$
	:i if NOT $gotParam$$min$
		:i %GLOBAL%$min$ = %f(90.000000)
	:i endif
	:i if NOT $gotParam$$max$
		:i %GLOBAL%$max$ = %f(150.000000)
	:i endif
	:i return$min$ = %GLOBAL%$min$$max$ = %GLOBAL%$max$
:i endfunction
*
* addition:
* 
:i %GLOBAL%min$ = %f(0.0)
:i %GLOBAL%$max$ = %f(NaN.0) //FFFFFFFF
:i return$min$ = %GLOBAL%$min$$max$ = %GLOBAL%$max$
:i endfunction
*/


const uint8_t skateshop_scaling_options_new1[] = {
	0x05, 0x03, 0x16, 0xF3, 0xAC, 0xE5, 0x84, 0x07, 0x1B, 0x0E, 0x00, 0x00, 0x00, 0x53, 0x43, 0x41, 0x4C, 0x45, 0x20, 0x4F, 0x50, 0x54, 0x49, 0x4F, 0x4E, 0x53, 0x00, 0x16, 0x38, 0x58, 0x74, 0xC4, 0x07, 0x1C, 0x05, 0x00, 0x00, 0x00, 0x42, 0x6F, 0x64, 0x79, 0x00, 0x16, 0xE7, 0xB7, 0x4F, 0x5B, 0x07, 0x16, 0x0E, 0xA1, 0x48, 0x27, 0x16, 0x34, 0xF4, 0x27, 0xAF, 0x16, 0x8E, 0x68, 0xA6, 0x6A, 0x07, 0x03, 0x16, 0xCE, 0x3E, 0x69, 0xD4, 0x16, 0x58, 0x0E, 0x6E, 0xA3, 0x16, 0xE2, 0x5F, 0x67, 0x3A, 0x16, 0x9F, 0x69, 0x35, 0xDA, 0x04, 0x16, 0x80, 0xD5, 0x68, 0x00, 0x07, 0x16, 0x58, 0x43, 0x31, 0x8B, 0x04, 0x03, 0x16, 0x38, 0x58, 0x74, 0xC4, 0x07, 0x1C, 0x09, 0x00, 0x00, 0x00, 0x48, 0x65, 0x61, 0x64, 0x20, 0x54, 0x6F, 0x70, 0x00, 0x16, 0xE7, 0xB7, 0x4F, 0x5B, 0x07, 0x16, 0x0E, 0xA1, 0x48, 0x27, 0x16, 0x34, 0xF4, 0x27, 0xAF, 0x16, 0x8E, 0x68, 0xA6, 0x6A, 0x07, 0x03, 0x16, 0xCE, 0x3E, 0x69, 0xD4, 0x16, 0x58, 0x0E, 0x6E, 0xA3, 0x16, 0xE2, 0x5F, 0x67, 0x3A, 0x16, 0x9F, 0x69, 0x35, 0xDA, 0x04, 0x16, 0x80, 0xD5, 0x68, 0x00, 0x07, 0x16, 0xD0, 0x08, 0x0F, 0xB9, 0x16, 0x3E, 0xF1, 0xF2, 0x7E, 0x07, 0x16, 0x63, 0x09, 0x0C, 0x58, 0x16, 0x3F, 0x62, 0xBC, 0x6E, 0x07, 0x16, 0x6D, 0xAB, 0x0F, 0x65, 0x16, 0x32, 0x54, 0x9D, 0x6C, 0x07, 0x16, 0xAE, 0x5B, 0xC8, 0x0F, 0x04, 0x03, 0x16, 0x38, 0x58, 0x74, 0xC4, 0x07, 0x1C, 0x05, 0x00, 0x00, 0x00, 0x46, 0x61, 0x63, 0x65, 0x00, 0x16, 0xE7, 0xB7, 0x4F, 0x5B, 0x07, 0x16, 0x0E, 0xA1, 0x48, 0x27, 0x16, 0x34, 0xF4, 0x27, 0xAF, 0x16, 0x8E, 0x68, 0xA6, 0x6A, 0x07, 0x03, 0x16, 0xCE, 0x3E, 0x69, 0xD4, 0x16, 0x58, 0x0E, 0x6E, 0xA3, 0x16, 0xE2, 0x5F, 0x67, 0x3A, 0x16, 0x9F, 0x69, 0x35, 0xDA, 0x04, 0x16, 0x80, 0xD5, 0x68, 0x00, 0x07, 0x16, 0x7F, 0xAB, 0x8F, 0xA2, 0x16, 0x3E, 0xF1, 0xF2, 0x7E, 0x07, 0x16, 0x63, 0x09, 0x0C, 0x58, 0x16, 0x3F, 0x62, 0xBC, 0x6E, 0x07, 0x16, 0x6D, 0xAB, 0x0F, 0x65, 0x16, 0x32, 0x54, 0x9D, 0x6C, 0x07, 0x16, 0xAE, 0x5B, 0xC8, 0x0F, 0x04, 0x03, 0x16, 0x38, 0x58, 0x74, 0xC4, 0x07, 0x1C, 0x05, 0x00, 0x00, 0x00, 0x4E, 0x6F, 0x73, 0x65, 0x00, 0x16, 0xE7, 0xB7, 0x4F, 0x5B, 0x07, 0x16, 0x0E, 0xA1, 0x48, 0x27, 0x16, 0x34, 0xF4, 0x27, 0xAF, 0x16, 0x8E, 0x68, 0xA6, 0x6A, 0x07, 0x03, 0x16, 0xCE, 0x3E, 0x69, 0xD4, 0x16, 0x58, 0x0E, 0x6E, 0xA3, 0x16, 0xE2, 0x5F, 0x67, 0x3A, 0x16, 0x9F, 0x69, 0x35, 0xDA, 0x04, 0x16, 0x80, 0xD5, 0x68, 0x00, 0x07, 0x16, 0xE8, 0xFA, 0xBC, 0x1D, 0x16, 0x3E, 0xF1, 0xF2, 0x7E, 0x07, 0x16, 0x63, 0x09, 0x0C, 0x58, 0x16, 0x3F, 0x62, 0xBC, 0x6E, 0x07, 0x16, 0x6D, 0xAB, 0x0F, 0x65, 0x16, 0x32, 0x54, 0x9D, 0x6C, 0x07, 0x16, 0xAE, 0x5B, 0xC8, 0x0F, 0x04, 0x03, 0x16, 0x38, 0x58, 0x74, 0xC4, 0x07, 0x1C, 0x04, 0x00, 0x00, 0x00, 0x6A, 0x61, 0x77, 0x00, 0x16, 0xE7, 0xB7, 0x4F, 0x5B, 0x07, 0x16, 0x0E, 0xA1, 0x48, 0x27, 0x16, 0x34, 0xF4, 0x27, 0xAF, 0x16, 0x8E, 0x68, 0xA6, 0x6A, 0x07, 0x03, 0x16, 0xCE, 0x3E, 0x69, 0xD4, 0x16, 0x58, 0x0E, 0x6E, 0xA3, 0x16, 0xE2, 0x5F, 0x67, 0x3A, 0x16, 0x9F, 0x69, 0x35, 0xDA, 0x04, 0x16, 0x80, 0xD5, 0x68, 0x00, 0x07, 0x16, 0xC1, 0xD3, 0x42, 0x04, 0x16, 0x3E, 0xF1, 0xF2, 0x7E, 0x07, 0x16, 0x63, 0x09, 0x0C, 0x58, 0x16, 0x3F, 0x62, 0xBC, 0x6E, 0x07, 0x16, 0x6D, 0xAB, 0x0F, 0x65, 0x16, 0x32, 0x54, 0x9D, 0x6C, 0x07, 0x16, 0xAE, 0x5B, 0xC8, 0x0F, 0x04, 0x03, 0x16, 0x38, 0x58, 0x74, 0xC4, 0x07, 0x1C, 0x06, 0x00, 0x00, 0x00, 0x43, 0x68, 0x65, 0x73, 0x74, 0x00, 0x16, 0xE7, 0xB7, 0x4F, 0x5B, 0x07, 0x16, 0x41, 0x56, 0xE6, 0x25, 0x16, 0x8E, 0x68, 0xA6, 0x6A, 0x07, 0x03, 0x16, 0xCE, 0x3E, 0x69, 0xD4, 0x16, 0x58, 0x0E, 0x6E, 0xA3, 0x16, 0xE2, 0x5F, 0x67, 0x3A, 0x16, 0x9F, 0x69, 0x35, 0xDA, 0x04, 0x16, 0x34, 0xF4, 0x27, 0xAF, 0x16, 0x80, 0xD5, 0x68, 0x00, 0x07, 0x16, 0x7A, 0x32, 0x07, 0xAF, 0x16, 0x3E, 0xF1, 0xF2, 0x7E, 0x07, 0x16, 0xE1, 0x8F, 0x77, 0xB1, 0x04, 0x03, 0x16, 0x38, 0x58, 0x74, 0xC4, 0x07, 0x1C, 0x06, 0x00, 0x00, 0x00, 0x57, 0x61, 0x69, 0x73, 0x74, 0x00, 0x16, 0xE7, 0xB7, 0x4F, 0x5B, 0x07, 0x16, 0x9F, 0x80, 0x22, 0x54, 0x16, 0x8E, 0x68, 0xA6, 0x6A, 0x07, 0x03, 0x16, 0xCE, 0x3E, 0x69, 0xD4, 0x16, 0x58, 0x0E, 0x6E, 0xA3, 0x16, 0xE2, 0x5F, 0x67, 0x3A, 0x16, 0x9F, 0x69, 0x35, 0xDA, 0x04, 0x16, 0x34, 0xF4, 0x27, 0xAF, 0x16, 0x80, 0xD5, 0x68, 0x00, 0x07, 0x16, 0xA4, 0xE4, 0xC3, 0xDE, 0x16, 0x3E, 0xF1, 0xF2, 0x7E, 0x07, 0x16, 0xE4, 0xCB, 0xC9, 0xE5, 0x04, 0x03, 0x16, 0x38, 0x58, 0x74, 0xC4, 0x07, 0x1C, 0x07, 0x00, 0x00, 0x00, 0x42, 0x69, 0x63, 0x65, 0x70, 0x73, 0x00, 0x16, 0xE7, 0xB7, 0x4F, 0x5B, 0x07, 0x16, 0xDA, 0x15, 0x65, 0xA0, 0x16, 0x8E, 0x68, 0xA6, 0x6A, 0x07, 0x03, 0x16, 0xCE, 0x3E, 0x69, 0xD4, 0x16, 0x58, 0x0E, 0x6E, 0xA3, 0x16, 0xE2, 0x5F, 0x67, 0x3A, 0x16, 0x9F, 0x69, 0x35, 0xDA, 0x04, 0x16, 0x34, 0xF4, 0x27, 0xAF, 0x16, 0x80, 0xD5, 0x68, 0x00, 0x07, 0x16, 0xE1, 0x71, 0x84, 0x2A, 0x16, 0x3E, 0xF1, 0xF2, 0x7E, 0x07, 0x16, 0xE1, 0x8F, 0x77, 0xB1, 0x04, 0x03, 0x16, 0x38, 0x58, 0x74, 0xC4, 0x07, 0x1C, 0x09, 0x00, 0x00, 0x00, 0x46, 0x6F, 0x72, 0x65, 0x61, 0x72, 0x6D, 0x73, 0x00, 0x16, 0xE7, 0xB7, 0x4F, 0x5B, 0x07, 0x16, 0xAB, 0xF4, 0xEC, 0x09, 0x16, 0x8E, 0x68, 0xA6, 0x6A, 0x07, 0x03, 0x16, 0xCE, 0x3E, 0x69, 0xD4, 0x16, 0x58, 0x0E, 0x6E, 0xA3, 0x16, 0xE2, 0x5F, 0x67, 0x3A, 0x16, 0x9F, 0x69, 0x35, 0xDA, 0x04, 0x16, 0x34, 0xF4, 0x27, 0xAF, 0x16, 0x80, 0xD5, 0x68, 0x00, 0x07, 0x16, 0x90, 0x90, 0x0D, 0x83, 0x16, 0x3E, 0xF1, 0xF2, 0x7E, 0x07, 0x16, 0xE1, 0x8F, 0x77, 0xB1, 0x04, 0x03, 0x16, 0x38, 0x58, 0x74, 0xC4, 0x07, 0x1C, 0x06, 0x00, 0x00, 0x00, 0x48, 0x61, 0x6E, 0x64, 0x73, 0x00, 0x16, 0xE7, 0xB7, 0x4F, 0x5B, 0x07, 0x16, 0xDC, 0x0E, 0xB1, 0x05, 0x16, 0x8E, 0x68, 0xA6, 0x6A, 0x07, 0x03, 0x16, 0xCE, 0x3E, 0x69, 0xD4, 0x16, 0x58, 0x0E, 0x6E, 0xA3, 0x16, 0xE2, 0x5F, 0x67, 0x3A, 0x16, 0x9F, 0x69, 0x35, 0xDA, 0x04, 0x16, 0x34, 0xF4, 0x27, 0xAF, 0x16, 0x80, 0xD5, 0x68, 0x00, 0x07, 0x16, 0xE7, 0x6A, 0x50, 0x8F, 0x16, 0x3E, 0xF1, 0xF2, 0x7E, 0x07, 0x16, 0x75, 0xBC, 0xE7, 0x02, 0x04, 0x03, 0x16, 0x38, 0x58, 0x74, 0xC4, 0x07, 0x1C, 0x07, 0x00, 0x00, 0x00, 0x54, 0x68, 0x69, 0x67, 0x68, 0x73, 0x00, 0x16, 0xE7, 0xB7, 0x4F, 0x5B, 0x07, 0x16, 0x62, 0x2D, 0xDC, 0x34, 0x16, 0x8E, 0x68, 0xA6, 0x6A, 0x07, 0x03, 0x16, 0xCE, 0x3E, 0x69, 0xD4, 0x16, 0x58, 0x0E, 0x6E, 0xA3, 0x16, 0xE2, 0x5F, 0x67, 0x3A, 0x16, 0x9F, 0x69, 0x35, 0xDA, 0x04, 0x16, 0x34, 0xF4, 0x27, 0xAF, 0x16, 0x80, 0xD5, 0x68, 0x00, 0x07, 0x16, 0x59, 0x49, 0x3D, 0xBE, 0x16, 0x3E, 0xF1, 0xF2, 0x7E, 0x07, 0x16, 0x75, 0xBC, 0xE7, 0x02, 0x04, 0x03, 0x16, 0x38, 0x58, 0x74, 0xC4, 0x07, 0x1C, 0x07, 0x00, 0x00, 0x00, 0x43, 0x61, 0x6C, 0x76, 0x65, 0x73, 0x00, 0x16, 0xE7, 0xB7, 0x4F, 0x5B, 0x07, 0x16, 0x13, 0xCC, 0x55, 0x9D, 0x16, 0x8E, 0x68, 0xA6, 0x6A, 0x07, 0x03, 0x16, 0xCE, 0x3E, 0x69, 0xD4, 0x16, 0x58, 0x0E, 0x6E, 0xA3, 0x16, 0xE2, 0x5F, 0x67, 0x3A, 0x16, 0x9F, 0x69, 0x35, 0xDA, 0x04, 0x16, 0x34, 0xF4, 0x27, 0xAF, 0x16, 0x80, 0xD5, 0x68, 0x00, 0x07, 0x16, 0x28, 0xA8, 0xB4, 0x17, 0x16, 0x3E, 0xF1, 0xF2, 0x7E, 0x07, 0x16, 0x68, 0x9E, 0x05, 0x94, 0x04, 0x03, 0x16, 0x38, 0x58, 0x74, 0xC4, 0x07, 0x1C, 0x05, 0x00, 0x00, 0x00, 0x46, 0x65, 0x65, 0x74, 0x00, 0x16, 0xE7, 0xB7, 0x4F, 0x5B, 0x07, 0x16, 0x5B, 0x50, 0xBC, 0x09, 0x16, 0x8E, 0x68, 0xA6, 0x6A, 0x07, 0x03, 0x16, 0xCE, 0x3E, 0x69, 0xD4, 0x16, 0x58, 0x0E, 0x6E, 0xA3, 0x16, 0xE2, 0x5F, 0x67, 0x3A, 0x16, 0x9F, 0x69, 0x35, 0xDA, 0x04, 0x16, 0x34, 0xF4, 0x27, 0xAF, 0x16, 0x80, 0xD5, 0x68, 0x00, 0x07, 0x16, 0x60, 0x34, 0x5D, 0x83, 0x16, 0x3E, 0xF1, 0xF2, 0x7E, 0x07, 0x16, 0x30, 0xAB, 0x08, 0xC1, 0x04, 0x03, 0x16, 0x38, 0x58, 0x74, 0xC4, 0x07, 0x1C, 0x06, 0x00, 0x00, 0x00, 0x42, 0x6F, 0x61, 0x72, 0x64, 0x00, 0x16, 0xE7, 0xB7, 0x4F, 0x5B, 0x07, 0x16, 0x0E, 0xA1, 0x48, 0x27, 0x16, 0x8E, 0x68, 0xA6, 0x6A, 0x07, 0x03, 0x16, 0xCE, 0x3E, 0x69, 0xD4, 0x16, 0x58, 0x0E, 0x6E, 0xA3, 0x16, 0xE2, 0x5F, 0x67, 0x3A, 0x16, 0x9F, 0x69, 0x35, 0xDA, 0x04, 0x16, 0x34, 0xF4, 0x27, 0xAF, 0x16, 0x80, 0xD5, 0x68, 0x00, 0x07, 0x16, 0x60, 0x34, 0x5D, 0x83, 0x16, 0x3E, 0xF1, 0xF2, 0x7E, 0x07, 0x16, 0xC8, 0xC9, 0x53, 0xB0, 0x16, 0x0B, 0x1F, 0xA4, 0x6C, 0x07, 0x16, 0x0B, 0x1F, 0xA4, 0x6C, 0x04, 0x06, 0x01
};









const uint8_t game_new[] = {
	0x01, 0x23, 0x16, 0x77, 0x77, 0x9B, 0x1D, 0x01, 0x16, 0x0A, 0x99, 0x5D, 0xCB, 0x17, 0x01, 0x00,
	0x00, 0x00, 0x01, 0x16, 0xBA, 0x1F, 0x31, 0x54, 0x17, 0x01, 0x00, 0x00, 0x00, 0x01, 0x24, 0x01,
	0x23, 0x16, 0x06, 0x35, 0x2E, 0xAA, 0x01, 0x16, 0x0A, 0x99, 0x5D, 0xCB, 0x17, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x16, 0xBA, 0x1F, 0x31, 0x54, 0x17, 0x00, 0x00, 0x00, 0x00, 0x01, 0x24, 0x01, 0x23,
	0x16, 0x3B, 0xCE, 0x02, 0x1D, 0x01, 0x47, 0x16, 0x00, 0x39, 0x16, 0x4B, 0x6B, 0xDA, 0x94, 0x01,
	0x16, 0x77, 0xB8, 0x8A, 0x5B, 0x42, 0x16, 0x0C, 0x57, 0x6B, 0x26, 0x01, 0x28, 0x01, 0x16, 0x28,
	0x0F, 0x83, 0x47, 0x01, 0x47, 0x4B, 0x00, 0x16, 0xE9, 0x6F, 0xDA, 0xA1, 0x01, 0x47, 0x1C, 0x00,
	0x39, 0x16, 0x4B, 0x6B, 0xDA, 0x94, 0x01, 0x16, 0x94, 0x7B, 0x2E, 0x41, 0x01, 0x16, 0x77, 0xB8,
	0x8A, 0x5B, 0x42, 0x16, 0x1E, 0x4F, 0xF4, 0x39, 0x01, 0x28, 0x01, 0x16, 0x82, 0xD9, 0x24, 0xB1,
	0x01, 0x47, 0x16, 0x00, 0x39, 0x16, 0x4B, 0x6B, 0xDA, 0x94, 0x01, 0x16, 0x77, 0xB8, 0x8A, 0x5B,
	0x42, 0x16, 0x9B, 0xBF, 0x66, 0xB8, 0x01, 0x28, 0x01, 0x16, 0x07, 0x63, 0x7D, 0x4C, 0x01, 0x28,
	0x01, 0x16, 0x36, 0xE3, 0xB6, 0x9E, 0x16, 0x8E, 0xBC, 0x34, 0xA1, 0x01, 0x24, 0x01, 0x23, 0x16,
	0x8E, 0xBC, 0x34, 0xA1, 0x01, 0x16, 0x0C, 0x89, 0x42, 0x0C, 0x01, 0x16, 0xEF, 0x1E, 0x4F, 0x95,
	0x01, 0x47, 0x2E, 0x00, 0x16, 0xE9, 0x6F, 0xDA, 0xA1, 0x01, 0x16, 0x9D, 0x8F, 0x95, 0xFF, 0x16,
	0xED, 0x16, 0x28, 0x33, 0x07, 0x16, 0xC8, 0xF1, 0x2F, 0x26, 0x01, 0x16, 0xF7, 0xB4, 0x7D, 0x3D,
	0x01, 0x16, 0x1F, 0x14, 0xA6, 0xCE, 0x01, 0x16, 0x2E, 0xBB, 0xA9, 0x11, 0x01, 0x48, 0x2C, 0x00,
	0x01, 0x16, 0x9D, 0x8F, 0x95, 0xFF, 0x16, 0xED, 0x16, 0x28, 0x33, 0x07, 0x16, 0xC8, 0xF1, 0x2F,
	0x26, 0x01, 0x16, 0xF7, 0xB4, 0x7D, 0x3D, 0x01, 0x16, 0x73, 0xA5, 0xF4, 0xD6, 0x16, 0x66, 0x5D,
	0x8F, 0x5C, 0x01, 0x16, 0x8D, 0x07, 0x6F, 0xE4, 0x01, 0x28, 0x01, 0x16, 0x1A, 0x7C, 0x11, 0x82,
	0x17, 0x02, 0x00, 0x00, 0x00, 0x16, 0x05, 0xDF, 0x37, 0xFC, 0x01, 0x16, 0xDF, 0x71, 0x9A, 0x58,
	0x01, 0x16, 0x1C, 0xAE, 0x1F, 0xD1, 0x01, 0x24, 0x01, 0x23, 0x16, 0x0B, 0x85, 0x4C, 0x5D, 0x01,
	0x16, 0x42, 0x99, 0xCE, 0x18, 0x16, 0xAF, 0x98, 0xC6, 0x40, 0x07, 0x16, 0x28, 0x5F, 0xF4, 0x6D,
	0x01, 0x16, 0x21, 0x7D, 0xE7, 0xAB, 0x16, 0x56, 0x4D, 0x41, 0x61, 0x07, 0x2D, 0x16, 0x56, 0x4D,
	0x41, 0x61, 0x01, 0x16, 0x1F, 0x14, 0xA6, 0xCE, 0x01, 0x24, 0x01, 0x23, 0x16, 0x9B, 0x8B, 0xA2,
	0x4B, 0x01, 0x16, 0x0B, 0x85, 0x4C, 0x5D, 0x01, 0x16, 0x2C, 0x43, 0x62, 0x35, 0x01, 0x24, 0x01,
	0x23, 0x16, 0xB3, 0x0E, 0xC7, 0x93, 0x01, 0x16, 0x1F, 0x14, 0xA6, 0xCE, 0x01, 0x16, 0x2C, 0x43,
	0x62, 0x35, 0x01, 0x24, 0x01, 0x23, 0x16, 0x8A, 0x37, 0xA6, 0xFB, 0x01, 0x16, 0x2C, 0xF2, 0xA3,
	0xE1, 0x01, 0x16, 0xB6, 0xE9, 0x15, 0x3C, 0x16, 0xAF, 0x98, 0xC6, 0x40, 0x07, 0x16, 0x83, 0x1D,
	0x3D, 0xF5, 0x01, 0x16, 0x54, 0x52, 0x42, 0xF0, 0x16, 0x85, 0xD2, 0xCE, 0xB1, 0x16, 0x24, 0xD6,
	0x6B, 0x9A, 0x07, 0x2D, 0x16, 0x24, 0xD6, 0x6B, 0x9A, 0x16, 0xD0, 0xD2, 0x4E, 0x86, 0x07, 0x16,
	0xB3, 0x0E, 0xC7, 0x93, 0x16, 0x7F, 0xD4, 0xB7, 0x5D, 0x07, 0x16, 0x9B, 0x8B, 0xA2, 0x4B, 0x16,
	0x78, 0xCE, 0x92, 0xA5, 0x07, 0x1B, 0x0E, 0x00, 0x00, 0x00, 0x45, 0x4E, 0x54, 0x45, 0x52, 0x20,
	0x4D, 0x45, 0x53, 0x53, 0x41, 0x47, 0x45, 0x00, 0x16, 0x70, 0x3B, 0xEF, 0x68, 0x07, 0x17, 0x00,
	0x00, 0x00, 0x00, 0x16, 0xC4, 0xA1, 0xE3, 0x69, 0x07, 0x17, 0x7F, 0x00, 0x00, 0x00, 0x16, 0x38,
	0x58, 0x74, 0xC4, 0x07, 0x1B, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x24, 0x01, 0x23, 0x16, 0xB8,
	0x48, 0x45, 0x3B, 0x01, 0x16, 0xDF, 0x01, 0xA8, 0xBF, 0x16, 0xCA, 0xAF, 0xCF, 0x7B, 0x07, 0x17,
	0x12, 0x02, 0x00, 0x00, 0x01, 0x16, 0x54, 0x52, 0x42, 0xF0, 0x16, 0x85, 0xD2, 0xCE, 0xB1, 0x16,
	0x9D, 0x56, 0xB7, 0x02, 0x16, 0x53, 0x19, 0x26, 0x7F, 0x07, 0x1F, 0x00, 0x00, 0xA0, 0x43, 0x00,
	0x00, 0x82, 0x43, 0x16, 0x7F, 0xD4, 0xB7, 0x5D, 0x07, 0x16, 0x0B, 0x85, 0x4C, 0x5D, 0x16, 0x79,
	0xB5, 0x1E, 0x4F, 0x07, 0x1B, 0x08, 0x00, 0x00, 0x00, 0x41, 0x42, 0x43, 0x41, 0x45, 0x3A, 0x20,
	0x00, 0x16, 0x78, 0xCE, 0x92, 0xA5, 0x07, 0x1B, 0x05, 0x00, 0x00, 0x00, 0x5A, 0x5A, 0x5A, 0x5A,
	0x00, 0x16, 0x70, 0x3B, 0xEF, 0x68, 0x07, 0x17, 0x01, 0x00, 0x00, 0x00, 0x16, 0xC4, 0xA1, 0xE3,
	0x69, 0x07, 0x17, 0x00, 0x02, 0x00, 0x00, 0x16, 0x80, 0xD2, 0x50, 0x2A, 0x01, 0x16, 0xDF, 0x01,
	0xA8, 0xBF, 0x16, 0xCA, 0xAF, 0xCF, 0x7B, 0x07, 0x17, 0x68, 0x01, 0x00, 0x00, 0x01, 0x24, 0x01,
	0x23, 0x16, 0xB2, 0xFE, 0xDA, 0xD4, 0x01, 0x16, 0xEA, 0xAD, 0x68, 0x70, 0x1A, 0x00, 0x00, 0xC8,
	0x42, 0x01, 0x24, 0x01, 0x23, 0x16, 0x73, 0xBE, 0xBD, 0xE1, 0x01, 0x16, 0xEA, 0xAD, 0x68, 0x70,
	0x17, 0x01, 0x00, 0x00, 0x00, 0x01, 0x24, 0x01, 0x2B, 0x77, 0x77, 0x9B, 0x1D, 0x50, 0x61, 0x75,
	0x73, 0x65, 0x4D, 0x75, 0x73, 0x69, 0x63, 0x41, 0x6E, 0x64, 0x53, 0x74, 0x72, 0x65, 0x61, 0x6D,
	0x73, 0x00, 0x2B, 0xBA, 0x1F, 0x31, 0x54, 0x50, 0x61, 0x75, 0x73, 0x65, 0x53, 0x74, 0x72, 0x65,
	0x61, 0x6D, 0x00, 0x2B, 0x4B, 0x6B, 0xDA, 0x94, 0x49, 0x73, 0x4F, 0x62, 0x73, 0x65, 0x72, 0x76,
	0x69, 0x6E, 0x67, 0x00, 0x2B, 0x77, 0xB8, 0x8A, 0x5B, 0x53, 0x6B, 0x61, 0x74, 0x65, 0x72, 0x00,
	0x2B, 0xE9, 0x6F, 0xDA, 0xA1, 0x49, 0x6E, 0x4E, 0x65, 0x74, 0x47, 0x61, 0x6D, 0x65, 0x00, 0x2B,
	0x94, 0x7B, 0x2E, 0x41, 0x45, 0x78, 0x69, 0x74, 0x53, 0x75, 0x72, 0x76, 0x65, 0x79, 0x6F, 0x72,
	0x4D, 0x6F, 0x64, 0x65, 0x00, 0x2B, 0x1E, 0x4F, 0xF4, 0x39, 0x61, 0x64, 0x64, 0x5F, 0x73, 0x6B,
	0x61, 0x74, 0x65, 0x72, 0x5F, 0x74, 0x6F, 0x5F, 0x77, 0x6F, 0x72, 0x6C, 0x64, 0x00, 0x2B, 0x82,
	0xD9, 0x24, 0xB1, 0x52, 0x65, 0x73, 0x65, 0x74, 0x50, 0x72, 0x6F, 0x53, 0x65, 0x74, 0x46, 0x6C,
	0x61, 0x67, 0x73, 0x00, 0x2B, 0x9B, 0xBF, 0x66, 0xB8, 0x52, 0x75, 0x6E, 0x53, 0x74, 0x61, 0x72,
	0x74, 0x65, 0x64, 0x00, 0x2B, 0x36, 0xE3, 0xB6, 0x9E, 0x53, 0x70, 0x61, 0x77, 0x6E, 0x53, 0x63,
	0x72, 0x69, 0x70, 0x74, 0x00, 0x2B, 0x8E, 0xBC, 0x34, 0xA1, 0x64, 0x6F, 0x5F, 0x73, 0x63, 0x72,
	0x65, 0x65, 0x6E, 0x5F, 0x66, 0x72, 0x65, 0x65, 0x7A, 0x65, 0x00, 0x2B, 0xEF, 0x1E, 0x4F, 0x95,
	0x50, 0x61, 0x75, 0x73, 0x65, 0x47, 0x61, 0x6D, 0x65, 0x00, 0x2B, 0x9D, 0x8F, 0x95, 0xFF, 0x65,
	0x78, 0x69, 0x74, 0x5F, 0x70, 0x61, 0x75, 0x73, 0x65, 0x5F, 0x6D, 0x65, 0x6E, 0x75, 0x00, 0x2B,
	0xED, 0x16, 0x28, 0x33, 0x6D, 0x65, 0x6E, 0x75, 0x5F, 0x69, 0x64, 0x00, 0x2B, 0xC8, 0xF1, 0x2F,
	0x26, 0x70, 0x61, 0x75, 0x73, 0x65, 0x5F, 0x6D, 0x65, 0x6E, 0x75, 0x00, 0x2B, 0xF7, 0xB4, 0x7D,
	0x3D, 0x66, 0x6F, 0x72, 0x63, 0x65, 0x5F, 0x63, 0x6C, 0x6F, 0x73, 0x65, 0x5F, 0x72, 0x61, 0x6E,
	0x6B, 0x69, 0x6E, 0x67, 0x73, 0x00, 0x2B, 0x1F, 0x14, 0xA6, 0xCE, 0x64, 0x65, 0x73, 0x74, 0x72,
	0x6F, 0x79, 0x5F, 0x6F, 0x6E, 0x73, 0x63, 0x72, 0x65, 0x65, 0x6E, 0x5F, 0x6B, 0x65, 0x79, 0x62,
	0x6F, 0x61, 0x72, 0x64, 0x00, 0x2B, 0x2E, 0xBB, 0xA9, 0x11, 0x53, 0x74, 0x61, 0x72, 0x74, 0x4E,
	0x65, 0x74, 0x77, 0x6F, 0x72, 0x6B, 0x4C, 0x6F, 0x62, 0x62, 0x79, 0x00, 0x2B, 0x73, 0xA5, 0xF4,
	0xD6, 0x53, 0x65, 0x74, 0x47, 0x61, 0x6D, 0x65, 0x54, 0x79, 0x70, 0x65, 0x00, 0x2B, 0x66, 0x5D,
	0x8F, 0x5C, 0x66, 0x72, 0x65, 0x65, 0x73, 0x6B, 0x61, 0x74, 0x65, 0x32, 0x70, 0x00, 0x2B, 0x1A,
	0x7C, 0x11, 0x82, 0x57, 0x61, 0x69, 0x74, 0x00, 0x2B, 0xDF, 0x71, 0x9A, 0x58, 0x75, 0x6E, 0x70,
	0x61, 0x75, 0x73, 0x65, 0x67, 0x61, 0x6D, 0x65, 0x00, 0x2B, 0x1C, 0xAE, 0x1F, 0xD1, 0x72, 0x65,
	0x74, 0x72, 0x79, 0x00, 0x2B, 0x42, 0x99, 0xCE, 0x18, 0x47, 0x65, 0x74, 0x54, 0x65, 0x78, 0x74,
	0x45, 0x6C, 0x65, 0x6D, 0x65, 0x6E, 0x74, 0x53, 0x74, 0x72, 0x69, 0x6E, 0x67, 0x00, 0x2B, 0xAF,
	0x98, 0xC6, 0x40, 0x69, 0x64, 0x00, 0x2B, 0x28, 0x5F, 0xF4, 0x6D, 0x6B, 0x65, 0x79, 0x62, 0x6F,
	0x61, 0x72, 0x64, 0x5F, 0x63, 0x75, 0x72, 0x72, 0x65, 0x6E, 0x74, 0x5F, 0x73, 0x74, 0x72, 0x69,
	0x6E, 0x67, 0x00, 0x2B, 0x21, 0x7D, 0xE7, 0xAB, 0x53, 0x65, 0x6E, 0x64, 0x43, 0x68, 0x61, 0x74,
	0x4D, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x00, 0x2B, 0x56, 0x4D, 0x41, 0x61, 0x73, 0x74, 0x72,
	0x69, 0x6E, 0x67, 0x00, 0x2B, 0x9B, 0x8B, 0xA2, 0x4B, 0x6D, 0x65, 0x6E, 0x75, 0x5F, 0x65, 0x6E,
	0x74, 0x65, 0x72, 0x65, 0x64, 0x5F, 0x63, 0x68, 0x61, 0x74, 0x5F, 0x6D, 0x65, 0x73, 0x73, 0x61,
	0x67, 0x65, 0x00, 0x2B, 0x2C, 0x43, 0x62, 0x35, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x5F, 0x70,
	0x61, 0x75, 0x73, 0x65, 0x5F, 0x6D, 0x65, 0x6E, 0x75, 0x00, 0x2B, 0x8A, 0x37, 0xA6, 0xFB, 0x6C,
	0x61, 0x75, 0x6E, 0x63, 0x68, 0x5F, 0x63, 0x68, 0x61, 0x74, 0x5F, 0x6B, 0x65, 0x79, 0x62, 0x6F,
	0x61, 0x72, 0x64, 0x00, 0x2B, 0x2C, 0xF2, 0xA3, 0xE1, 0x68, 0x69, 0x64, 0x65, 0x5F, 0x63, 0x75,
	0x72, 0x72, 0x65, 0x6E, 0x74, 0x5F, 0x67, 0x6F, 0x61, 0x6C, 0x00, 0x2B, 0xB6, 0xE9, 0x15, 0x3C,
	0x44, 0x65, 0x73, 0x74, 0x72, 0x6F, 0x79, 0x53, 0x63, 0x72, 0x65, 0x65, 0x6E, 0x45, 0x6C, 0x65,
	0x6D, 0x65, 0x6E, 0x74, 0x00, 0x2B, 0x83, 0x1D, 0x3D, 0xF5, 0x63, 0x75, 0x72, 0x72, 0x65, 0x6E,
	0x74, 0x5F, 0x6D, 0x65, 0x6E, 0x75, 0x5F, 0x61, 0x6E, 0x63, 0x68, 0x6F, 0x72, 0x00, 0x2B, 0x54,
	0x52, 0x42, 0xF0, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x5F, 0x6F, 0x6E, 0x73, 0x63, 0x72, 0x65,
	0x65, 0x6E, 0x5F, 0x6B, 0x65, 0x79, 0x62, 0x6F, 0x61, 0x72, 0x64, 0x00, 0x2B, 0x85, 0xD2, 0xCE,
	0xB1, 0x61, 0x6C, 0x6C, 0x6F, 0x77, 0x5F, 0x63, 0x61, 0x6E, 0x63, 0x65, 0x6C, 0x00, 0x2B, 0x24,
	0xD6, 0x6B, 0x9A, 0x69, 0x63, 0x6F, 0x6E, 0x00, 0x2B, 0xD0, 0xD2, 0x4E, 0x86, 0x6B, 0x65, 0x79,
	0x62, 0x6F, 0x61, 0x72, 0x64, 0x5F, 0x63, 0x61, 0x6E, 0x63, 0x65, 0x6C, 0x5F, 0x73, 0x63, 0x72,
	0x69, 0x70, 0x74, 0x00, 0x2B, 0x7F, 0xD4, 0xB7, 0x5D, 0x6B, 0x65, 0x79, 0x62, 0x6F, 0x61, 0x72,
	0x64, 0x5F, 0x64, 0x6F, 0x6E, 0x65, 0x5F, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x00, 0x2B, 0x78,
	0xCE, 0x92, 0xA5, 0x6B, 0x65, 0x79, 0x62, 0x6F, 0x61, 0x72, 0x64, 0x5F, 0x74, 0x69, 0x74, 0x6C,
	0x65, 0x00, 0x2B, 0x70, 0x3B, 0xEF, 0x68, 0x6D, 0x69, 0x6E, 0x5F, 0x6C, 0x65, 0x6E, 0x67, 0x74,
	0x68, 0x00
};

// 2B is start of checksum table, exclude from there