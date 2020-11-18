//// 
////  Font data for Bauhaus 93 12pt
//// 

//// Character bitmaps for Bauhaus 93 12pt
//const uint8_t bauhaus93_12ptBitmaps[] = 
//{
//	// @0 '!' (4 pixels wide)
//	0xE0, // ### 
//	0xE0, // ### 
//	0xE0, // ### 
//	0xE0, // ### 
//	0xE0, // ### 
//	0xE0, // ### 
//	0xE0, // ### 
//	0x60, //  ## 
//	0xF0, // ####
//	0xF0, // ####
//	0x60, //  ## 

//	// @11 '-' (3 pixels wide)
//	0x00, //    
//	0x00, //    
//	0x00, //    
//	0x00, //    
//	0x00, //    
//	0xE0, // ###
//	0xE0, // ###
//	0x00, //    
//	0x00, //    
//	0x00, //    
//	0x00, //    

//	// @22 '4' (7 pixels wide)
//	0x1E, //    ####
//	0x3E, //   #####
//	0x3E, //   #####
//	0x3E, //   #####
//	0x6E, //  ## ###
//	0x7E, //  ######
//	0xFE, // #######
//	0xFE, // #######
//	0x0E, //     ###
//	0x0E, //     ###
//	0x0E, //     ###

//	// @33 'A' (8 pixels wide)
//	0x3E, //   ##### 
//	0x7F, //  #######
//	0xFF, // ########
//	0xE7, // ###  ###
//	0xE7, // ###  ###
//	0xF7, // #### ###
//	0xF7, // #### ###
//	0xF7, // #### ###
//	0xE7, // ###  ###
//	0xE7, // ###  ###
//	0xE7, // ###  ###

//	// @44 'B' (8 pixels wide)
//	0xFE, // ####### 
//	0xFF, // ########
//	0xFF, // ########
//	0xE7, // ###  ###
//	0xEE, // ### ### 
//	0xEE, // ### ### 
//	0xEF, // ### ####
//	0xE7, // ###  ###
//	0xEF, // ### ####
//	0xEF, // ### ####
//	0xEE, // ### ### 

//	// @55 'C' (12 pixels wide)
//	0x1F, 0x00, //    #####    
//	0x3F, 0xC0, //   ########  
//	0x7F, 0xE0, //  ########## 
//	0xF1, 0xE0, // ####   #### 
//	0xE0, 0xF0, // ###     ####
//	0xE0, 0x00, // ###         
//	0xE0, 0xF0, // ###     ####
//	0xF1, 0xE0, // ####   #### 
//	0x7F, 0xE0, //  ########## 
//	0x3F, 0xC0, //   ########  
//	0x1F, 0x00, //    #####    

//	// @77 'E' (6 pixels wide)
//	0x7C, //  #####
//	0xFC, // ######
//	0xFC, // ######
//	0xE0, // ###   
//	0xFC, // ######
//	0xFC, // ######
//	0xFC, // ######
//	0xE0, // ###   
//	0xFC, // ######
//	0xFC, // ######
//	0x7C, //  #####

//	// @88 'G' (9 pixels wide)
//	0x1E, 0x00, //    ####  
//	0x3E, 0x00, //   #####  
//	0x7E, 0x00, //  ######  
//	0xF0, 0x00, // ####     
//	0xE0, 0x00, // ###      
//	0xE7, 0x00, // ###  ### 
//	0xE7, 0x80, // ###  ####
//	0xF7, 0x80, // #### ####
//	0x7F, 0x80, //  ########
//	0x3F, 0x00, //   ###### 
//	0x1E, 0x00, //    ####  

//	// @110 'I' (3 pixels wide)
//	0xE0, // ###
//	0xE0, // ###
//	0xE0, // ###
//	0xE0, // ###
//	0xE0, // ###
//	0xE0, // ###
//	0xE0, // ###
//	0xE0, // ###
//	0xE0, // ###
//	0xE0, // ###
//	0xE0, // ###

//	// @121 'L' (4 pixels wide)
//	0xE0, // ### 
//	0xE0, // ### 
//	0xE0, // ### 
//	0xE0, // ### 
//	0xE0, // ### 
//	0xE0, // ### 
//	0xE0, // ### 
//	0xE0, // ### 
//	0xF0, // ####
//	0x70, //  ###
//	0x30, //   ##

//	// @132 'M' (11 pixels wide)
//	0x7B, 0xC0, //  #### #### 
//	0xFF, 0xE0, // ###########
//	0xFF, 0xE0, // ###########
//	0xEE, 0xE0, // ### ### ###
//	0xEE, 0xE0, // ### ### ###
//	0xEE, 0xE0, // ### ### ###
//	0xEE, 0xE0, // ### ### ###
//	0xEE, 0xE0, // ### ### ###
//	0xEE, 0xE0, // ### ### ###
//	0xEE, 0xE0, // ### ### ###
//	0xEE, 0xE0, // ### ### ###

//	// @154 'N' (8 pixels wide)
//	0x3C, //   ####  
//	0x7E, //  ###### 
//	0xFF, // ########
//	0xE7, // ###  ###
//	0xE7, // ###  ###
//	0xE7, // ###  ###
//	0xE7, // ###  ###
//	0xE7, // ###  ###
//	0xE7, // ###  ###
//	0xE7, // ###  ###
//	0xE7, // ###  ###

//	// @165 'O' (12 pixels wide)
//	0x1F, 0x80, //    ######   
//	0x3F, 0xC0, //   ########  
//	0x7F, 0xE0, //  ########## 
//	0xF0, 0xF0, // ####    ####
//	0xE0, 0x70, // ###      ###
//	0xE0, 0x70, // ###      ###
//	0xE0, 0x70, // ###      ###
//	0xF0, 0xF0, // ####    ####
//	0x7F, 0xE0, //  ########## 
//	0x3F, 0xC0, //   ########  
//	0x1F, 0x80, //    ######   

//	// @187 'P' (8 pixels wide)
//	0x3C, //   ####  
//	0x7E, //  ###### 
//	0xFF, // ########
//	0xE7, // ###  ###
//	0xEF, // ### ####
//	0xEF, // ### ####
//	0xEE, // ### ### 
//	0xE0, // ###     
//	0xE0, // ###     
//	0xE0, // ###     
//	0xE0, // ###     

//	// @198 'R' (9 pixels wide)
//	0xFC, 0x00, // ######   
//	0xFE, 0x00, // #######  
//	0xFF, 0x00, // ######## 
//	0xE7, 0x00, // ###  ### 
//	0xE7, 0x00, // ###  ### 
//	0xEF, 0x00, // ### #### 
//	0xEE, 0x00, // ### ###  
//	0xEE, 0x00, // ### ###  
//	0xEF, 0x00, // ### #### 
//	0xE7, 0x00, // ###  ### 
//	0xE7, 0x80, // ###  ####

//	// @220 'S' (5 pixels wide)
//	0x38, //   ###
//	0x38, //   ###
//	0x78, //  ####
//	0x70, //  ### 
//	0x70, //  ### 
//	0x78, //  ####
//	0x38, //   ###
//	0x38, //   ###
//	0xF8, // #####
//	0xF0, // #### 
//	0xE0, // ###  

//	// @231 'T' (8 pixels wide)
//	0xFF, // ########
//	0xFF, // ########
//	0xFF, // ########
//	0x1C, //    ###  
//	0x1C, //    ###  
//	0x1C, //    ###  
//	0x1C, //    ###  
//	0x1C, //    ###  
//	0x1C, //    ###  
//	0x1C, //    ###  
//	0x1C, //    ###  

//	// @242 'W' (11 pixels wide)
//	0xEE, 0xE0, // ### ### ###
//	0xEE, 0xE0, // ### ### ###
//	0xEE, 0xE0, // ### ### ###
//	0xEE, 0xE0, // ### ### ###
//	0xEE, 0xE0, // ### ### ###
//	0xEE, 0xE0, // ### ### ###
//	0xEE, 0xE0, // ### ### ###
//	0xEE, 0xE0, // ### ### ###
//	0xFF, 0xE0, // ###########
//	0xFF, 0xE0, // ###########
//	0x7B, 0xC0, //  #### #### 
//};

//// Character descriptors for Bauhaus 93 12pt
//// { [Char width in bits], [Offset into bauhaus93_12ptCharBitmaps in bytes] }
//const FONT_CHAR_INFO bauhaus93_12ptDescriptors[] = 
//{
//	{4, 0}, 		// ! 
//	{0, 0}, 		// " 
//	{0, 0}, 		// # 
//	{0, 0}, 		// $ 
//	{0, 0}, 		// % 
//	{0, 0}, 		// & 
//	{0, 0}, 		// ' 
//	{0, 0}, 		// ( 
//	{0, 0}, 		// ) 
//	{0, 0}, 		// * 
//	{0, 0}, 		// + 
//	{0, 0}, 		// , 
//	{3, 11}, 		// - 
//	{0, 0}, 		// . 
//	{0, 0}, 		// / 
//	{0, 0}, 		// 0 
//	{0, 0}, 		// 1 
//	{0, 0}, 		// 2 
//	{0, 0}, 		// 3 
//	{7, 22}, 		// 4 
//	{0, 0}, 		// 5 
//	{0, 0}, 		// 6 
//	{0, 0}, 		// 7 
//	{0, 0}, 		// 8 
//	{0, 0}, 		// 9 
//	{0, 0}, 		// : 
//	{0, 0}, 		// ; 
//	{0, 0}, 		// < 
//	{0, 0}, 		// = 
//	{0, 0}, 		// > 
//	{0, 0}, 		// ? 
//	{0, 0}, 		// @ 
//	{8, 33}, 		// A 
//	{8, 44}, 		// B 
//	{12, 55}, 		// C 
//	{0, 0}, 		// D 
//	{6, 77}, 		// E 
//	{0, 0}, 		// F 
//	{9, 88}, 		// G 
//	{0, 0}, 		// H 
//	{3, 110}, 		// I 
//	{0, 0}, 		// J 
//	{0, 0}, 		// K 
//	{4, 121}, 		// L 
//	{11, 132}, 		// M 
//	{8, 154}, 		// N 
//	{12, 165}, 		// O 
//	{8, 187}, 		// P 
//	{0, 0}, 		// Q 
//	{9, 198}, 		// R 
//	{5, 220}, 		// S 
//	{8, 231}, 		// T 
//	{0, 0}, 		// U 
//	{0, 0}, 		// V 
//	{11, 242}, 		// W 
//};

//// Font information for Bauhaus 93 12pt
//const FONT_INFO bauhaus93_12ptFontInfo =
//{
//	2, //  Character height
//	'!', //  Start character
//	'W', //  End character
//	2, //  Width, in pixels, of space character
//	bauhaus93_12ptDescriptors, //  Character descriptor array
//	bauhaus93_12ptBitmaps, //  Character bitmap array
//};
