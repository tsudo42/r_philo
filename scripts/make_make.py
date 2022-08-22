#!/usr/bin/env python3
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    make_make.py                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#              #
#    Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########         #
#                                                                              #
# **************************************************************************** #

from glob import glob
from make_template import *

def get_body(dirname, acro=None):
	if acro is None:
		acro = dirname[0].upper()
	else:
		acro = acro.upper()
	lines = []
	lines.append("\n")
	lines.append("SRCS	+= $(" + acro + "_SRCS)\n")
	lines.append(acro + "_SRCS	:= \\\n")
	lines.extend(["\t" + name + " \\\n" for name in glob("srcs/" + dirname + "/*.c")])
	return (lines)

def update_makefile():
	with open("Makefile", mode='w') as fobj:
		fobj.write(MAKEFILE_PART1)
		fobj.writelines(get_body("system"))
		fobj.writelines(get_body("philo"))
		fobj.writelines(get_body("utils"))
		fobj.writelines(get_body("debug"))
		fobj.write(MAKEFILE_PART2)

if __name__ == "__main__":
	update_makefile()
