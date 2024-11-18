import math

Noc = 60 # число работающих на объекте связи, чел
# обеспеченность противогазами = 55%
R3 = 2.18 # расстояние от узла связи до АХОВ, км
# в-во - фосген
p = 1.42 # удельная плотность, т/м^3
G = 85 # кол-во АХОВ, т
# способ хранения - обвалованная ёмкость
d = 0.45 # толщина слоя разлива АХОВ, м
v = 2 # скорость ветра в приземном слое, м/с

# площадь разлива АХОВ
Sp = G / (p * d)
print('Sp =', Sp, 'м^2')
# радиус разлива АХОВ
rp = pow(Sp / math.pi, 1/2)
print('rp =', rp, 'м')
# длина и ширина разлива АХОВ
l = b = 2 * rp
print('l, b =', l, ',', b, 'м')
Гизот = 19 # глубина распространения облака АХОВ при изотермии, км
Гизот /= 1.5 # из-за обвалованной ёмкости
Гинв = Гизот * 5 # при инверсии, км
Гконв = Гизот / 5 # при конвекции, км
print('Гизот =', Гизот, 'км, Гинв =', Гинв, 'км, Гконв =', Гконв, 'км')
# v > 1 => поправочные коэффициенты
Гизот *= 0.7; Гинв *= 0.6; Гконв *= 0.7
print('С поправкой на скорость ветра: Гизот =', Гизот, 'км, Гинв =', Гинв, 'км, Гконв =', Гконв, 'км')
# ширина зоны заражения для случаев вертикальной устойчивости воздуха
Шизот = Гизот * 0.15 # при изотермии, км
Шинв = Гинв * 0.03 # при инверсии, км
Шконв = Гконв * 0.8 # при конвекции, км
print('Шизот =', Шизот, 'км, Шинв =', Шинв, 'км, Шконв =', Шконв, 'км\n')

# средняя скорость переноса заражённого воздуха воздушным потоком
vcp = v
if R3 >= 10:
    vcp *= 2
    print('R3 > 10, vcp =', vcp, 'м/с')
else:
    vcp *= 1.5
    print('R3 < 10, vcp =', vcp, 'м/с')
# время подхода облака к объекту связи
R3 *= 1000 # переводим в метры
tподх = R3 / (60 * vcp)
print('tподх =', tподх, 'мин\n')

# время поражающего действия АХОВ
tисп = tпораж = 23 * 0.55
print('tисп = tпораж =', tисп, 'ч\n')

# возможные потери среди персонала УС
П = Noc * 0.27
print('П =', П, 'чел')
print('Лёгкой степени =', П * 0.25, 'чел')
print('Средней и тяжёлой степени =', П * 0.4, 'чел')
print('Со смертельным исходом =', П * 0.35, 'чел')
