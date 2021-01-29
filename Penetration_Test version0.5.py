from math import cos, pi
def normalization_fn(normalization, caliber, n_armor): #function for normalization angle for n_armour < 3 * caliber
    normalization = normalization * 1.4 * float(caliber) / int(n_armor)
    return round(normalization, 3)

def e_armor_fn(n_armor, angle, normalization):                   #function for effective armor after normalization
    e_armor = round(int(n_armor) / cos((float(angle) - normalization) * pi / 180), 3)
    return e_armor
    
def e_armor1_fn(n_armor, angle):                                 #function for effective armor
    e_armor1 = round(int(n_armor) / cos((float(angle)) * pi / 180), 3)
    return e_armor1

def penetration_rng_fn(penetrated, penetration, e_armor):
    string = ''
    for i in range(-5,6):                                        #penetration rng
        if round(float(penetration)* (1 + i / 100), 3) > e_armor: 
            penetrated += 1
        if i < 0:
            string += 'rng ' + str(i) + '%, penetration ' + str(round(float(penetration)* (1 + i / 100), 3)) + 'mm' + '|'
        else:
            string += 'rng ' + str(i) + '%, penetration ' + str(round(float(penetration)* (1 + i / 100), 3)) + 'mm' + '|'
    
    chance = round(penetrated / 11 * 100, 2)                     #chance of penetration
    return chance, string

def penetration_calculator(caliber, shell, penetration):
    penetrated = 0           #rng +-5% rng count for penetrated shells
    if shell == 'ap':
        normalization = 5    #ap normalization angle                                                                           
        auto_ricochet = 70   #ap auto ricochet angle
    elif shell == 'apcr':
        normalization = 2    #apcr normalization angle
        auto_ricochet = 70   #apcr auto ricochet angle
    elif shell == 'heat':
        auto_ricochet = 85   #heat auto ricochet angle
    else:
        auto_ricochet = 100  #he/hesh/hep
    if shell == ('ap' or 'apcr'):                                                                            #ap apcr shell penetration tests
        if int(angle) >= auto_ricochet:                                                                      #entry angle 70* or more test
            if float(caliber) > 3 * int(n_armor):                                                              #3 caliber's rule test
                normalization = normalization_fn(normalization, caliber, n_armor)                            #high caliber ap gets normalization boost
                e_armor = e_armor_fn(n_armor, angle, normalization)                                          #effective armor against high caliber ap
                e_armor1 = e_armor1_fn(n_armor, angle)                                                       #actual effective thickness
                return penetration_rng_fn(penetrated, penetration, e_armor)
            else:                                                                                            #medium to low caliber ap bounced
                print()
                print('Auto-ricochet')
                print()
        else:                                                                                                #2 caliber's rule test
            if float(caliber) > 2 * int(n_armor):
                normalization = normalization_fn(normalization, caliber, n_armor)                            #medium caliber ap gets normalization boost
                e_armor = e_armor_fn(n_armor, angle, normalization)                                          #effective armor against medium caliber ap
                e_armor1 = e_armor1_fn(n_armor, angle)                                                       #actual effective thickness
                return penetration_rng_fn(penetrated, penetration, e_armor)                                                                            
            else:                                                                                            #low caliber ap penetration test
                e_armor = e_armor_fn(n_armor, angle, normalization)                                          #effective armor against low caliber ap
                e_armor1 = e_armor1_fn(n_armor, angle)                                                       #actual effective thickness
                return penetration_rng_fn(penetrated, penetration, e_armor)
    elif shell == 'heat':
        if float(angle) >= auto_ricochet:
            print()
            print('Auto-ricochet')
            print()
        else:
            e_armor = e_armor1_fn(n_armor, angle)                                                                #effective armor against heat/he
            return penetration_rng_fn(penetrated, penetration, e_armor)
    else:
        e_armor = e_armor1_fn(n_armor, angle)                                                                #effective armor against heat/he
        return penetration_rng_fn(penetrated, penetration, e_armor)

tier9 = ('Against Light Tanks', 'T92E1,152,apcr,210,heat,310', 'Bat.-Châtillon 25t AP,100,ap,232,apcr,263', 'Vickers Cruiser,105,apcr,245,heat,290',
         'Against Medium Tanks', 'T-54,100,ap,219,heat,270', 'T-54,100,ap,201,heat,270', 'T54E1,105,ap,230,apcr,270', 'M46 Patton,105,ap,218,apcr,265', 'Centurion Mk.7/1,105,hesh,210,apcr,255', 'Centurion Mk.7/1,105,apcr,255,heat,300', 'T 55A,100,ap,219,heat,270', 'Type 61,105,apcr,245,heat,300', 'Leopard Prototyp A,105,apcr,255,heat,300', 'E 50,105,ap,220,apcr,270', 'AMX 30 1er prototype,105,ap,232,apcr,263', 'Prototipo Standard B,105,apcr,240,heat,295', 'Wz 120,122,ap,220,heat,280',
         'Against Heavy Tanks', 'K-91,100,ap,248,heat,310', 'IS-8,122,ap,258,heat,340', 'ST-I,122,ap,258,heat,340', 'M103,120,ap,258,heat,340', 'Conqueror,120,ap,259,apcr,326', 'Mäuschen,128,ap,246,apcr,311', 'KpfPz 70,152,apcr,240,heat,305', 'E 75,128,ap,246,apcr,311', 'VK 45.02 (P) Ausf.B,128,ap,246,apcr,311', 'AMX 50 120,120,ap,257,apcr,340', 'Emil II,120,apcr,252,heat,300', '50TP prototyp,122,ap,258,apcr,340', 'WZ-111 model 1-4,130,ap,246,heat,320',
         'Against Tds','SU-122-54,122,ap,258,heat,340', 'Object 704,152,ap,286,apcr,329', 'T95,152,ap,276,apcr,320', 'T30,152,ap,276,apcr,320', 'FV4004 Conway,139.7,ap,260,hesh,200', 'FV4004 Conway,120,ap,259,apcr,326', 'Tortoise,120,ap,259,apcr,326', 'Ho-Ri Type II,150,ap,290,ap,340', 'Waffenträger auf Pz. IV,150,ap,255,heat,334', 'Waffenträger auf Pz. IV,128,ap,276,apcr,352', 'Jagdtiger,128,ap,276,apcr,352', 'AMX 50 Foch,120,ap,260,apcr,320', 'WZ-111G FT,152,ap,290,heat,375')
tier10 = ('','')

while 1:
    print('Enter nominal armor thickness, angle of entry of shell and by what tier you would like to compare:') #taking input of armour, angle and tier
    n_armor, angle, tier = input().split()
    if tier == '9':
        for i in range(0, len(tier9)):
            if tier9[i] == 'Against Light Tanks':
                print('________________Against Light Tanks________________')
                print()
            elif tier9[i] == 'Against Medium Tanks':
                print()
                print('________________Against Medium Tanks________________')
                print()
            elif tier9[i] == 'Against Heavy Tanks':
                print()
                print('________________Against Heavy Tanks________________')
                print()
            elif tier9[i] == 'Against Tds':
                print()
                print('________________Against Tds________________')
                print()
            else:
                name_of_tank, caliber, s_shell, s_penetration, p_shell, p_penetration = tier9[i].split(',')
                print(name_of_tank)
                penetration_calculator(caliber, s_shell, s_penetration)
                chance = penetration_calculator(caliber, s_shell, s_penetration)[0]
                string = penetration_calculator(caliber, s_shell, s_penetration)[1].replace('|', '\n')
                if chance == 100.0:                                             #if standard rounds without calibrated shell has 100% chance of penetration
                    print('can penetrate this with standard rounds without calibration.')
                else:                                                            #if standard shell does not have 100% chance of penetration, then check calibrated
                    print('can penetrate this with standard rounds without calibration by chance of', str(chance) + '%')
                    if s_shell == ('ap' or 'apcr'):                              #calibration for standard ap/apcr rounds
                        s_penetration = str(float(s_penetration) * 1.05)
                        penetration_calculator(caliber, s_shell, s_penetration)
                    else:                                                        #calibration for standard other rounds
                        s_penetration = str(float(s_penetration) * 1.1)
                        penetration_calculator(caliber, s_shell, s_penetration)
                    if chance == 100.0:                                         #if calibrated standard shell has 100% chance of penetration
                        print('can penetrate this with calibrated standard shells.')
                    else:                                                        #if calibrated standard shell has less than 100%, switch to gold
                        print('can penetrate this with calibrated standard shells by chance of', str(chance) + '%')
                        penetration_calculator(caliber, p_shell, p_penetration)
                        if chance == 100.0:                                     #if gold rounds without calibrated shells has 100% chance of penetration
                            print('can penetrate this with premium shells without calibration.')
                        else:                                                    ##if gold round does not have 100% chance of penetration, then check calibrated
                            print('can penetrate this with premium shells without calibration by chance of', str(chance) + '%')
                            if p_shell == ('ap' or 'apcr'):                      #calibration for prammo ap/apcr
                                s_penetration = str(float(s_penetration) * 1.05)
                                penetration_calculator(caliber, p_shell, p_penetration)
                            else:                                                #calibration for standard other rounds
                                s_penetration = str(float(s_penetration) * 1.1)
                                penetration_calculator(caliber, p_shell, p_penetration)
                            if chance == 100.0:
                                print('can penetrate this with calibrated premium shells.')
                            elif chance == 0.0:
                                print('can not penetrate this much armor at all.')
                            else:
                                print('can penetrate this with calibrated premium shells by chance of', str(chance) + '%')
                print()
                    
                        
    
#name_of_tank, caliber, s_shell, s_penetration, p_shell, p_penetration
#penetration_calculator(caliber, shell, penetration)
