import os
import argparse
import random as rnd

base = {1:'ichi',
		2:'ni',
		3:'san',
		4:'yon',
		5:'go',
		6:'roku',
		7:'nana',
		8:'hachi',
		9:'kyu'}
mult = {1:'',
		10:'ju',
		100:'hyaku',
		1000:'sen',
		10000:'man',
		100000000:'oku'}

def interpreter_irregulars(minor,rest,multiplier):
	if (minor == 3 and multiplier == 100):
		return 'san byaku '
	elif (minor == 6 and multiplier == 100):
		return 'ro ppyaku '
	elif (minor == 8 and multiplier == 100):
		return 'ha ppyaku '
	elif (minor == 3 and multiplier == 1000):
		return 'san zen '
	elif (minor == 8 and multiplier == 1000):
		return 'has sen '
	elif (minor == 1 and multiplier == 1000) and rest > 0:
		return 'is sen '
	return ''

def interpreter(number):
	return interpreter_rec('',number,1)
def interpreter_rec(str,number,multiplier):
	if number <= 0:
		if not str:
			return 'zero'
		else:
			return str
	else:
		#print("Number: {} Multiplier: {} Str: {}".format(number,multiplier,str))
		minor = number%10
		rest = (number-minor)/10
		# Irregulars
		add_str = interpreter_irregulars(minor,rest,multiplier)
		if not add_str:
			if minor > 0:
				add_str = mult[multiplier] + ' ' + add_str
			if minor > 1 or (minor == 1 and (multiplier==1 or multiplier==10000 or multiplier==100000000)):
				add_str = base[minor] + ' ' + add_str
		str = add_str + str
		return interpreter_rec(str,rest,multiplier*10)

if __name__ == "__main__":
	num = rnd.randint(0,100000)
	str = interpreter(num)
	print(" {}  {}".format(num,str))
