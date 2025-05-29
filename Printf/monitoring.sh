# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    monitoring.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anieto-m <anieto-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/29 14:47:32 by anieto-m          #+#    #+#              #
#    Updated: 2025/05/29 14:47:42 by anieto-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

wall "	# Architecture: $(uname -a)
	# CPU physical: $(grep 'physical id' /proc/cpuinfo | sort -u | wc -l)
	# vCPU: $(nproc)
	# Memory Usage: $(free -m | awk 'NR==2{printf "%s/%sMB (%.2f%%)", $3, $2, $3 * 100 / $2}')
	# Disk Usage: $(df -h --total | awk '/total/ {printf "%s/%s (%s)", $3, $2, $5}')
	# CPU load: $(top -bn1 | grep "Cpu(s)" | awk '{printf "%.1f%%", $2 + $4}')
	# Last boot: $(who -b | awk '{print $3, $4}')
	# LVM use: $(lsblk | grep -q "lvm" && echo yes || echo no)
	# Connections TCP: $(ss -t | grep ESTAB | wc -l) ESTABLISHED
	# User log: $(who | wc -l)
	# Network: IP $(hostname -I) / MAC $(ip link show | awk '/ether/ {print $2}')
	# Sudo: $(journalctl _COMM=sudo | grep COMMAND | wc -l) cmd"

