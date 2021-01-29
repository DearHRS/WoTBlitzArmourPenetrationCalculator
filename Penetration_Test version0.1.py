#effective armour = nominal_thickness/cos(x), x is in degrees
#2 caliber's rule => total_normalization(deg) = base_normalization(deg) * 1,4 * caliber(mm) / nominal_thickness
#3 caliber's rule => caliber(mm)> 3 * nominal_thickness
#heat shells lose penetration by 0.05% every 1 mm = heat_penetration - 0,05 * heat_penetration after every mm
from math import cos, pi
while 1:
    print('for ap/apcr penetration check press 1, for heat penetration check press 2:')
    x = int(input())
    if x == 1:
        while 1:
            penetrated = 0
            print('enter "ap" or "apcr", caliber, penetration, nominal armor and shell entry angle all in one same line with space seperating them:')
            shell, caliber, penetration, n_armor, angle = input().split()
            if shell == "apcr":
                normalization = 2
            else:
                normalization = 5
            if int(angle) >= 70:                                                                                         #entry angle 70* or more test
                if int(caliber) > 3 * int(n_armor):                                                                  #3 caliber's rule test
                    normalization = normalization * 1.4 * int(caliber) / int(n_armor)                            #high caliber ap gets normalization boost
                    e_armor = round(int(n_armor) / cos((int(angle) - normalization) * pi / 180), 3)              #effective armor against high caliber ap
                    e_armor1 = round(int(n_armor) / cos((int(angle)) * pi / 180), 3)                             #actual effective thickness
                    for i in range(-5,6):                                                                        #penetration rng
                        if round(int(penetration)* (1 + i / 100), 3) > e_armor: 
                            penetrated += 1
                        if i < 0:
                            print('rng', str(i)+ '%, penetration',str(round(int(penetration)* (1 + i / 100), 3)) + 'mm')
                        else:
                            print('rng ', str(i)+ '%, penetration',str(round(int(penetration)* (1 + i / 100), 3)) + 'mm')
                        chance = penetrated / 11 * 100
                    if chance == 0:                                                                             #failed to penetrate by high caliber ap
                        print()
                        print('Failed to penetrate!')
                        print(str(e_armor)+ 'mm of effective armor against', caliber + 'mm', shell + ', actual thickness', str(round(e_armor1))+'mm.')
                        print()    
                    else:
                        print()
                        print('Chance of penetration', str(round(chance, 2)) + '%')                          #penetrated by high caliber ap
                        print(str(e_armor)+ 'mm of effective armor against', caliber + 'mm', shell + ', actual thickness', str(round(e_armor1))+'mm.')
                        print()
                else:                                                                                                #medium to low caliber ap bounced
                    print()
                    print('Auto-ricochet')
                    print()
        else:                                                                                                        #2 caliber's rule test
            if int(caliber) > 2 * int(n_armor):
                normalization = normalization * 1.4 * int(caliber) / int(n_armor)                            #medium caliber ap gets normalization boost
                e_armor = round(int(n_armor) / cos((int(angle) - normalization) * pi / 180), 3)              #effective armor against medium caliber ap
                e_armor1 = round(int(n_armor) / cos((int(angle)) * pi / 180), 3)                             #actual effective thickness
                for i in range(-5,6):                                                                        #penetration rng
                    if round(int(penetration)* (1 + i / 100), 3) > e_armor: 
                        penetrated += 1
                    if i < 0:
                        print('rng', str(i)+ '%, penetration',str(round(int(penetration)* (1 + i / 100), 3)) + 'mm')
                    else:
                        print('rng ', str(i)+ '%, penetration',str(round(int(penetration)* (1 + i / 100), 3)) + 'mm')
                    chance = penetrated / 11 * 100
                if chance == 0:                                                                              #failed to penetrate by medium caliber ap
                    print()
                    print('Failed to penetrate!')
                    print(str(e_armor)+ 'mm of effective armor against', caliber + 'mm', shell + ', actual thickness', str(round(e_armor1))+'mm.')
                    print()    
                else:
                    print()
                    print('Chance of penetration', str(round(chance, 2)) + '%')                          #penetrated by medium caliber ap
                    print(str(e_armor)+ 'mm of effective armor against', caliber + 'mm', shell + ', actual thickness', str(round(e_armor1))+'mm.')
                    print()                                                                              
            else:                                                                                                #low caliber ap penetration test
                normalization = normalization * 1.4 * int(caliber) / int(n_armor)                            #low caliber ap gets normalization boost
                e_armor = round(int(n_armor) / cos((int(angle) - normalization) * pi / 180), 3)              #effective armor against low caliber ap
                e_armor1 = round(int(n_armor) / cos((int(angle)) * pi / 180), 3)                             #actual effective thickness
                for i in range(-5,6):                                                                        #penetration rng
                    if round(int(penetration)* (1 + i / 100), 3) > e_armor: 
                        penetrated += 1
                    if i < 0:
                        print('rng', str(i)+ '%, penetration',str(round(int(penetration)* (1 + i / 100), 3)) + 'mm')
                    else:
                        print('rng ', str(i)+ '%, penetration',str(round(int(penetration)* (1 + i / 100), 3)) + 'mm')
                    chance = penetrated / 11 * 100
                if chance == 0:                                                                              #failed to penetrate by low caliber ap
                    print()
                    print('Failed to penetrate!')
                    print(str(e_armor)+ 'mm of effective armor against', caliber + 'mm', shell + ', actual thickness', str(round(e_armor1))+'mm.')
                    print()    
                else:
                    print()
                    print('Chance of penetration', str(round(chance, 2)) + '%')                          #penetrated by low caliber ap
                    print(str(e_armor)+ 'mm of effective armor against', caliber + 'mm', shell + ', actual thickness', str(round(e_armor1))+'mm.')
                    print()
    else:
        heat_dist = input()
        heat_pen = int(heat_dist[:heat_dist.find(' ')])
        dist_mm = int(heat_dist[heat_dist.find(' ') + 1:])
        for i in range(0, dist_mm):
            heat_pen = heat_pen - 0.05 * heat_pen
        print(round(heat_pen, 3), "mm")
