from math import cos, pi
def take_input():               #takes input from user, if few values are missing uses default value
    print('______________________________________________________________________________')
    print('|Advanced: nominal armor, angle, tier, tank type and range:                  |') #taking input of nominal armor, angle, tier, tank type and shooting range
    print('|____________________________________________________________________________|') #example: 100 60 10 lt 250, seperate values with space
    print('|Enter nominal armor thickness, angle of entry of shell and against what tier|')
    print('|example: 100 60 10, seperate values with space                              |')
    print('|____________________________________________________________________________|')
    x = ['100', '60', '10', 'all', 100]  #default values : n_armor, angle, tier, tank_type, shooting_range
    x1 = input().split()        #input values
    for i in range(0, len(x1)): #replacing default values by input values
        x[i] = x1[i]
    return x

def normalization_fn(normalization, caliber, n_armor): #function for normalization angle for n_armour < 3 * caliber
    normalization = normalization * 1.4 * float(caliber) / float(n_armor)
    return round(normalization, 3)

def e_armor_fn(n_armor, angle, normalization):                   #function for effective armor after normalization
    e_armor = round(float(n_armor) / cos((float(angle) - normalization) * pi / 180), 3)
    return e_armor

def penetration_rng_fn(penetration = 0, e_armor = 0):
    penetrated = 0                                               #rng +-5% rng count for penetrated shells
    string = ''
    for i in range(-5,6):                                        #penetration rng                            
        if i < 0:                                                #detailed rng penetration levels
            if round(float(penetration)* (1 + i / 100), 3) > e_armor:
                penetrated += 1 
                string += 'rng ' + str(i) + '%, penetration ' + str(round(float(penetration)* (1 + i / 100), 3)) + 'mm  +' + '|'
            else:
                string += 'rng ' + str(i) + '%, penetration ' + str(round(float(penetration)* (1 + i / 100), 3)) + 'mm' + '|'
        else:
            if round(float(penetration)* (1 + i / 100), 3) > e_armor:
                penetrated += 1 
                string += 'rng  ' + str(i) + '%, penetration ' + str(round(float(penetration)* (1 + i / 100), 3)) + 'mm  +' + '|'
            else:
                string += 'rng  ' + str(i) + '%, penetration ' + str(round(float(penetration)* (1 + i / 100), 3)) + 'mm' + '|'
    
    chance = round(penetrated / 11 * 100, 2)                     #chance of penetration
    return chance, string, e_armor

def penetration_calculator(caliber, shell, penetration):
    if shell == 'ap' or shell == 'ap+':
        normalization = 5    #ap normalization angle                                                                           
        auto_ricochet = 70   #ap auto ricochet angle
    elif shell == 'apcr' or shell == 'apcr+':
        normalization = 2    #apcr normalization angle
        auto_ricochet = 70   #apcr auto ricochet angle
    elif shell == 'heat':
        auto_ricochet = 85   #heat auto ricochet angle
    else:
        auto_ricochet = 100  #he/hesh/hep
    if shell == 'ap' or shell == 'apcr' or shell == 'ap+' or shell == 'apcr+':                               #ap apcr shell penetration tests
        if float(angle) >= auto_ricochet:                                                                    #entry angle 70* or more test
            if float(caliber) > 3 * int(n_armor):                                                            #3 caliber's rule test
                normalization = normalization_fn(normalization, caliber, n_armor)                            #high caliber ap gets normalization boost
                e_armor = e_armor_fn(n_armor, angle, normalization)                                          #effective armor against high caliber ap
                return penetration_rng_fn(penetration, e_armor)
            else:                                                                                            #medium to low caliber ap bounced
                chance = 0
                string = ''
                e_armor = e_armor_fn(n_armor, angle, normalization)                                          #effective armor against high caliber ap
                print()
                print('Auto-ricochet for', shell)
                print()
                return chance, string, e_armor
        else:                                                                                                #if shell angle is not 70*
            if float(caliber) > 2 * int(n_armor):
                normalization = normalization_fn(normalization, caliber, n_armor)                            #medium caliber ap gets normalization boost
                e_armor = e_armor_fn(n_armor, angle, normalization)                                          #effective armor against medium caliber ap
                return penetration_rng_fn(penetration, e_armor)                                                                            
            else:                                                                                            #low caliber ap penetration test
                e_armor = e_armor_fn(n_armor, angle, normalization)                                          #effective armor against low caliber ap
                return penetration_rng_fn(penetration, e_armor)
    elif shell == 'heat':
        if float(angle) >= auto_ricochet:
            chance = 0
            string = ''
            e_armor = e_armor_fn(n_armor, angle, 0)                                                                #effective armor against heat/he
            print()
            print('Auto-ricochet for', shell)
            print()
            return chance, string, e_armor
        else:
            e_armor = e_armor_fn(n_armor, angle, 0)                                                                #effective armor against heat/he
            return penetration_rng_fn(penetration, e_armor)
    else:
        e_armor = e_armor_fn(n_armor, angle, 0)                                                                #effective armor against heat/he
        return penetration_rng_fn(penetration, e_armor)

def details(name_of_tank, caliber, s_shell, s_penetration, p_shell, p_penetration): #tests if standard can penetrate or calibrated, or gold or calibrated
    #name_of_tank = name, caliber, s_shell = standard shell name, s_penetration = standard shell penetration
    #p_shell = premium shell name, p_penetration = premium shell penetration
    print(name_of_tank)
    failed_to_penetrate = 0
    chance_string_e_armor = penetration_calculator(caliber, s_shell, s_penetration)
    chance = chance_string_e_armor[0]
    string = chance_string_e_armor[1].replace('|', '\n')
    e_armor = str(chance_string_e_armor[2])
    if chance == 100:                                                #if standard rounds without calibrated shell has 100% chance of penetration
        print(str(chance)+ '% chance to penetrate', e_armor + 'mm by', s_shell,'without calibration.')
    else:                                                            #if standard shell does not have 100% chance of penetration, then check calibrated
        if chance != 0:
            print(str(chance)+ '% chance to penetrate', e_armor + 'mm by', s_shell,'without calibration.')
            print(string)
        if s_shell == 'ap' or s_shell == 'apcr' or s_shell == 'ap+' or s_shell == 'apcr+':                              
            s_penetration = str(float(s_penetration) * 1.05)         #calibration for standard ap/apcr rounds
            chance_string_e_armor = penetration_calculator(caliber, s_shell, s_penetration)
            chance = chance_string_e_armor[0]
            string = chance_string_e_armor[1].replace('|', '\n')
            e_armor = str(chance_string_e_armor[2])
        else:                                                        
            s_penetration = str(float(s_penetration) * 1.1)          #calibration for standard other rounds
            chance_string_e_armor = penetration_calculator(caliber, s_shell, s_penetration)
            chance = chance_string_e_armor[0]
            string = chance_string_e_armor[1].replace('|', '\n')
            e_armor = str(chance_string_e_armor[2])
        s_e_armor = e_armor                                          #effective armor against standard shell
        if chance == 100:                                            #if calibrated standard shell has 100% chance of penetration
            print(str(chance)+ '% chance to penetrate', e_armor + 'mm by calibrated', s_shell)
        else:                                                        #if calibrated standard shell has less than 100%
            if chance != 0:
                print(str(chance)+ '% chance to penetrate', e_armor + 'mm by calibrated', s_shell)
                print(string)
    #switching to gold            
            chance_string_e_armor = penetration_calculator(caliber, p_shell, p_penetration)
            chance = chance_string_e_armor[0]
            string = chance_string_e_armor[1].replace('|', '\n')
            e_armor = str(chance_string_e_armor[2])
            if chance == 100:                                        #if gold rounds without calibrated shells has 100% chance of penetration
                print(str(chance)+ '% chance to penetrate', e_armor + 'mm by', p_shell,'without calibration.')
            else:                                                    #if gold round does not have 100% chance of penetration, then check calibrated
                if chance != 0:
                    print(str(chance)+ '% chance to penetrate', e_armor + 'mm by', p_shell,'without calibration.')
                    print(string)
                if p_shell == 'ap' or p_shell == 'apcr' or p_shell == 'ap+' or p_shell == 'apcr+':
                    p_penetration = str(float(p_penetration) * 1.05) #calibration for prammo ap/apcr
                    chance_string_e_armor = penetration_calculator(caliber, p_shell, p_penetration)
                    chance = chance_string_e_armor[0]
                    string = chance_string_e_armor[1].replace('|', '\n')
                    e_armor = str(chance_string_e_armor[2])
                else:                                                #calibration for prammo other rounds
                    p_penetration = str(float(p_penetration) * 1.1)
                    chance_string_e_armor = penetration_calculator(caliber, p_shell, p_penetration)
                    chance = chance_string_e_armor[0]
                    string = chance_string_e_armor[1].replace('|', '\n')
                    e_armor = str(chance_string_e_armor[2])
                p_e_armor = e_armor                                 #effective armor against premium shell
                if chance == 100:                                   #if chance is 100%
                    print(str(chance)+ '% chance to penetrate', e_armor + 'mm by calibrated', p_shell)
                elif chance == 0:                                   #if chance is 0%
                    failed_to_penetrate = 1
                    print('can not penetrate', n_armor + 'mm plate at', angle + '*')
                    print('effective thickness', s_e_armor + 'mm against its', s_shell)
                    print('effective thickness', p_e_armor + 'mm against its', p_shell)
                else:                                               #if chance is in between
                    print(str(chance)+ '% chance to penetrate', e_armor + 'mm by calibrated', p_shell)
                    print(string)
    print()
    return failed_to_penetrate
#all the data
Tank_data = ['9',
             'lt', 'T92E1,152,apcr,210,heat,310', 'Bat.-Châtillon 25t AP,100,ap,232,apcr,263', 'Vickers Cruiser,105,apcr,245,heat,290',
             'mt', 'T-54 (pen gun),100,ap,219,heat,270', 'T-54 (dpm gun),100,ap,201,heat,270', 'T54E1,105,ap,230,apcr,270', 'M46 Patton,105,ap,218,apcr,265', 'Centurion Mk.7/1 (chad hesh gun),105,hesh,210,apcr,255', 'Centurion Mk.7/1 (poopoo heat gun),105,apcr,255,heat,300', 'T 55A,100,ap,219,heat,270', 'Type 61,105,apcr,245,heat,300', 'Leopard Prototyp A,105,apcr,255,heat,300', 'E 50,105,ap,220,apcr,270', 'AMX 30 1er prototype,105,ap,232,apcr,263', 'Prototipo Standard B,105,apcr,240,heat,295', 'Wz 120,122,ap,220,heat,280',
             'ht', 'K-91,100,ap,248,heat,310', 'IS-8,122,ap,258,heat,340', 'ST-I,122,ap,258,heat,340', 'M103,120,ap,258,heat,340', 'Conqueror,120,ap,259,apcr,326', 'Mäuschen,128,ap,246,apcr,311', 'KpfPz 70,152,apcr,240,heat,305', 'E 75,128,ap,246,apcr,311', 'VK 45.02 (P) Ausf.B,128,ap,246,apcr,311', 'AMX 50 120,120,ap,257,apcr,340', 'Emil II,120,apcr,252,heat,300', '50TP prototyp,122,ap,258,apcr,340', 'WZ-111 model 1-4,130,ap,246,heat,320',
             'td','SU-122-54,122,ap,258,heat,340', 'Object 704,152,ap,286,apcr,329', 'T95,152,ap,276,apcr,320', 'T30,152,ap,276,apcr,320', 'FV4004 Conway (hesh gun),139.7,ap,260,hesh,200', 'FV4004 Conway (stock gun),120,ap,259,apcr,326', 'Tortoise,120,ap,259,apcr,326', 'Ho-Ri Type II,150,ap,290,ap+,340', 'Waffenträger auf Pz. IV (15cm),150,ap,255,heat,334', 'Waffenträger auf Pz. IV (12.8)cm,128,ap,276,apcr,352', 'Jagdtiger,128,ap,276,apcr,352', 'AMX 50 Foch,120,ap,260,apcr,320', 'WZ-111G FT,152,ap,290,heat,375',
             '10',
             'lt', 'Bat.-Châtillon 25 t,105,apcr,240,heat,295', 'Vickers Light,105,apcr,245,heat,290', 'XM551 Sheridan,152,apcr,230,heat,310',
             'mt', 'T-22 medium,100,apcr,240,heat,300', 'Object 140,100,ap,240,heat,290', 'T-62A,100,apcr,245,heat,300', 'M60,105,apcr,250,heat,300', 'M48 Patton,105,apcr,250,heat,300', 'FV4202(chad hesh gun),105,hesh,210,apcr,255', 'FV4202(poopoo heat gun),105,apcr,255,heat,300', 'STB-1,105,apcr,245,heat,300', 'Leopard 1,105,apcr,255,heat,300', 'E 50 Ausf. M,105,apcr,245,heat,300', 'AMX 30 B,105,apcr,250,heat,295', 'TVP T 50/51,100,apcr,242,heat,290', 'Progetto M40 mod. 65,105,apcr,245,heat,295', '121B,105,apcr,245,heat,300', 'WZ-121,122,ap,244,heat,290',
             'ht', 'IS-7,130,ap,260,apcr,303', 'IS-4,122,ap,258,heat,340', 'T95E6,120,ap,258,heat,340', 'T57 Heavy Tank,120,ap,258,heat,340', 'T110E5,120,ap,258,heat,340', 'Super Conqueror,120,ap,259,apcr,326', 'Chieftain Mk.6,120,apcr,260,apcr+,310', 'FV215b,120,ap,259,apcr,326', 'VK 90.01 (P),128,ap,275,apcr,320', 'VK 72.01 (K),150,ap,258,heat,334', 'E 100,150,ap,258,heat,334', 'Maus,120,ap,246,apcr,311', 'AMX M4 mle. 54,130,ap,265,ap+,310', 'AMX 50 B,120,ap,257,apcr,340', 'Kranvagn,120,ap,258,heat,340', 'WZ-111 model 5A,130,ap,260,heat,303', 'WZ-113,122,apcr,255,heat,335',
             'td', 'Object 263,130,ap,290,apcr,330', 'Object 268,152,ap,303,heat,380', 'T110E3,155,ap,295,apcr,375', 'T110E4,155,ap,295,apcr,375', 'FV4005,123,ap,280,apcr,370', 'FV217 Badger,123,ap,280,apcr,370', 'FV215b (183),183,hesh,220,ap,310', 'Ho-Ri Type III,150,ap,310,ap+,380', 'Grille 15,150,ap,279,heat,334', 'Jagdpanzer E 100,170,ap,299,heat,380', 'AMX 50 Foch (155),155,ap,280,heat,370', 'WZ-113G FT,152,ap,290,heat,375',
             '11']  #'11' needs to be here, because I am using a simple algorithm to break every data into their respectible variables

while 1:
    n_armor, angle, tier, tank_type, shooting_range = take_input() #value order: n_armor, angle, tier, tank_type, shooting_range
    data_= Tank_data[Tank_data.index(tier) + 1 : Tank_data.index(str(int(tier) + 1))]   #obtaining the requested part of tank data
    print('Armor test of', n_armor +'mm armor plate at', angle + '*', 'against Tier', tier)
    summarization = ''                      #summary to post at end
    failed_count = 0
    if tank_type == 'all':                  #armor test against all tank types
        lt_failed_count = 0
        mt_failed_count = 0
        ht_failed_count = 0
        td_failed_count = 0
        total_tanks = len(data_) - 4        #Number of selected tanks
        total_lt = len(data_[: data_.index('mt')]) - 1
        mt_coord = data_.index('mt')        #location of start of mediums
        total_mt = len(data_[data_.index('mt') : data_.index('ht')]) - 1
        ht_coord = data_.index('ht')        #location of start of heabies
        total_ht = len(data_[data_.index('ht') : data_.index('td')]) - 1
        td_coord = data_.index('td')        #location of start of mediums
        total_td = len(data_[data_.index('td') :]) - 1        
        for i in range(0, len(data_)):
            if data_[i] == 'lt':
                tankTP = data_[i]
                print('________________[Light Tanks]________________')
                print()
            elif data_[i] == 'mt':
                tankTP = data_[i]
                print()
                print('________________[Medium Tanks]________________')
                print()
            elif data_[i] == 'ht':
                tankTP = data_[i]
                print()
                print('________________[Heavy Tanks]________________')
                print()
            elif data_[i] == 'td':
                tankTP = data_[i]
                print()
                print('______________[Tank destroyers]______________')
                print()
            else:
                name_of_tank, caliber, s_shell, s_penetration, p_shell, p_penetration = data_[i].split(',')
                if i < mt_coord:
                    #s_shell = standard shell, s_penetration = standard penetration, p_shell = premium shell, p_penetration = premium penetration   
                    lt_failed_count += details(name_of_tank, caliber, s_shell, s_penetration, p_shell, p_penetration)
                elif i > mt_coord and i < ht_coord:
                    mt_failed_count += details(name_of_tank, caliber, s_shell, s_penetration, p_shell, p_penetration)
                elif i > ht_coord and i < td_coord: 
                    ht_failed_count += details(name_of_tank, caliber, s_shell, s_penetration, p_shell, p_penetration)
                else:
                    td_failed_count += details(name_of_tank, caliber, s_shell, s_penetration, p_shell, p_penetration)
                failed_count = lt_failed_count + mt_failed_count + ht_failed_count + td_failed_count
    elif tank_type == 'lt':
        lt_ = data_[: data_.index('mt')]                                                           #striping data to only light tanks
        total_tanks = len(lt_) - 1        #Number of selected tanks
        for i in range(0, len(lt_)):
            if lt_[i] == 'lt':
                tankTP = data_[i]
                print('________________[Light Tanks]________________')
                print()
            else:
                name_of_tank, caliber, s_shell, s_penetration, p_shell, p_penetration = lt_[i].split(',')
                #s_shell = standard shell, s_penetration = standard penetration, p_shell = premium shell, p_penetration = premium penetration   
                failed_count += details(name_of_tank, caliber, s_shell, s_penetration, p_shell, p_penetration)
        
    elif tank_type == 'mt':                                                                       #armor test against medium tanks
        mt_ = data_[data_.index('mt') : data_.index('ht')]                                        #striping data to only medium tanks
        total_tanks = len(mt_) - 1        #Number of selected tanks
        for i in range(0, len(mt_)):
            if mt_[i] == 'mt':
                tankTP = data_[i]
                print('________________[Medium Tanks]________________')
                print()
            else:
                name_of_tank, caliber, s_shell, s_penetration, p_shell, p_penetration = mt_[i].split(',')
                #s_shell = standard shell, s_penetration = standard penetration, p_shell = premium shell, p_penetration = premium penetration   
                failed_count += details(name_of_tank, caliber, s_shell, s_penetration, p_shell, p_penetration)
        
    elif tank_type == 'ht':                                                                       #armor test against heavy tanks
        ht_ = data_[data_.index('ht') : data_.index('td')]                                        #striping data to only heavy tanks
        total_tanks = len(ht_) - 1        #Number of selected tanks
        for i in range(0, len(ht_)):
            if ht_[i] == 'ht':
                tankTP = data_[i]
                print('________________[Heavy Tanks]________________')
                print()
            else:
                name_of_tank, caliber, s_shell, s_penetration, p_shell, p_penetration = ht_[i].split(',')
                #s_shell = standard shell, s_penetration = standard penetration, p_shell = premium shell, p_penetration = premium penetration   
                failed_count += details(name_of_tank, caliber, s_shell, s_penetration, p_shell, p_penetration)
        
    else:                                                                                         #armor test against tank destroyers
        td_ = data_[data_.index('td') :]                                                          #striping data to only tank destroyers
        total_tanks = len(td_) - 1        #Number of selected tanks
        for i in range(0, len(td_)):
            if td_[i] == 'td':
                tankTP = data_[i]
                print('______________[Tank destroyers]______________')
                print()
            else:
                name_of_tank, caliber, s_shell, s_penetration, p_shell, p_penetration = td_[i].split(',')
                #s_shell = standard shell, s_penetration = standard penetration, p_shell = premium shell, p_penetration = premium penetration   
                failed_count += details(name_of_tank, caliber, s_shell, s_penetration, p_shell, p_penetration)

#summary part of le code

                
    print('Armor performance summary:')
    print(n_armor + 'mm armor plate at',angle + '* :')
    print('effective thickness against ap:', str(e_armor_fn(n_armor, angle, 5))+ 'mm')
    print('                          apcr:', str(e_armor_fn(n_armor, angle, 2))+ 'mm')
    print('                       heat/he:', str(e_armor_fn(n_armor, angle, 0))+ 'mm')
    if failed_count == 0:                                                                     # Printing if all can penetrate
        print(' all of them laddies can penetrate')
        print('-----------------------------------')
    else:
        print('', failed_count,'out of',total_tanks,'tanks can not penetrate')                # Printing number of tanks that failed to penetrate
        print('--------------------------------------------------------------')
        if tank_type == 'all':
            if lt_failed_count == 0:                                                          # performance of lights
                print()
                print('o.o all light tonks can penetrate')
            elif lt_failed_count == total_lt:
                print()
                print('all light tanks failed to penetrate')
            else:
                print()
                print(lt_failed_count, 'out of', total_lt, 'light tanks failed to penetrate')
            if mt_failed_count == 0:                                                          # performance of mediums
                print()
                print('all medium tanks can penetrate')
            elif mt_failed_count == total_mt:
                print()
                print('all medium tanks failed to penetrate')
            else:
                print()
                print(mt_failed_count, 'out of', total_mt, 'medium tanks failed to penetrate')
            if ht_failed_count == 0:                                                          # performance of heabies
                print()
                print('all heavy tanks can penetrate')
            elif ht_failed_count == total_ht:
                print()
                print('all heavy tanks failed to penetrate')
            else:
                print()
                print(ht_failed_count, 'out of', total_ht, 'heavy tanks failed to penetrate')
            if td_failed_count == 0:                                                          # performance of tank destroyers
                print()
                print('all tank destroyers can penetrate')
                print()
            elif td_failed_count == total_td:
                print()
                print('all tank destroyers failed to penetrate, that armor plate is big no no no')
                print()
            else:
                print()
                print(td_failed_count, 'out of', total_td, 'tank destroyers failed to penetrate')
                print()
        else:                                                                                # performance if not all selected
            if failed_count == total_tanks:
                print()
                print('none of the can penetrate')
            else:
                print()
                print(failed_count, 'out of', total_tanks, 'tanks failed to penetrate')
            

    
    #summary(data_for_summary.append(name_of_tank + tankTP + s_shell + str(chance)))
    #data_for_summary = ()                                                          #summary string to return at end
    #print(summarization)

                    
'''                                         What I am aiming for
effective armor against      ap ....              done
effective armor against    apcr ....              done
effective armor against heat/he ....              done

tanks that failed to penetrate:                   done
    how many failed                               done
    which type                                    done

rate armor based of chance


tank that penetrated:
    ez clap chance:
    Name and shell type

    good chance:
    Name and shell type

    about 50/50 chance:
    Name and shell type

    rng blessing chance:
    Name and shell type
'''
#what details() gets name_of_tank, caliber, s_shell, s_penetration, p_shell, p_penetration
#def summary(data_for_details):  #tankNAME, tankTYPE, which_shell, chance
#    chance = 'yolo'
    


