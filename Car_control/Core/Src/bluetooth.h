
#define Song_off_cmd 	'0'
#define Song_1_cmd 		'1'
#define Song_2_cmd		'2'
#define Song_3_cmd		'3'
#define Song_4_cmd		'4'
#define Song_5_cmd		'5'
#define Song_6_cmd		'6'
#define Song_7_cmd		'7'

#define Lamp1_on 	'x'
#define Lamp1_off 'y'

#define Lamp2_on 	'c'
#define Lamp2_off 'd'

#define Lamp3_on 	'h'
#define Lamp3_off 'i'

#define Lamp4_on 	'j'
#define Lamp4_off 'k'

#define Lamp5_on 	'm'
#define Lamp5_off 'n'

void sendString(char *data_ptr);
extern char humString[8];
extern char tempString[8];

#define Car_forward_cmd 	'f'
#define Car_right_cmd			'r'
#define Car_left_cmd			'l'
#define Car_backward_cmd	'b'
#define Car_stop_cmd			'p'