from visual import *
# *****************************
# en el caso del tuple, se tiene (sin resistencia, con resistencia)
rad = 20.0               # Radios de los proyectiles
v0 = (100.0, 100.0)      # Velocidades iniciales de los proyectiles
m = 60.0                 # Masa de los proyectiles
b = 3.5                  # Resistencia del aire
g = 9.81                 # Magnitud de la gravedad
theta = 45.0             # Angulo de lanzamiento en degrees
dt = 0.001               # Paso del tiempo
# *****************************


def next_step(g_func, x_0, y_0, v_0, h):
    def f(v):
        return v

    kn = h * f(v_0)
    ln = h * g_func(x_0, y_0, v_0)
    kn += 2.0 * h * f(v_0 + (ln / 2.0))
    ln += 2.0 * h * g_func(x_0 + (h / 2.0), y_0 + (kn / 2.0), v_0 + (ln / 2.0))
    kn += 2.0 * h * f(v_0 + (ln / 2.0))
    ln += 2.0 * h * g_func(x_0 + (h / 2.0), y_0 + (kn / 2.0), v_0 + (ln / 2.0))
    kn += h * f(v_0 + ln)
    ln += h * g_func(x_0 + h, y_0 + kn, v_0 + ln)
    x_0 += h
    y_0 += (1.0 / 6.0) * kn
    v_0 += (1.0 / 6.0) * ln
    return y_0, v_0


theta = theta * pi / 180
xmax = fmax(v0[0], v0[1]) ** 2 * sin(2 * theta) / g
if xmax < 1:
    xmax = (fmax(v0[0], v0[1]) ** 2 * sin(theta) ** 2) / (2 * g)
if xmax < 1:
    xmax = 3.0*rad

px = (-xmax / 2.0, -xmax / 2.0)
py = (0.0 + rad, 0.0 + rad)
scene.center = (xmax / 8, xmax / 8, xmax / 16)
scene.fullscreen = true
scene.forward = (-0.5, -0.5, -1)
fl = box(length=xmax + (xmax * 0.1), height=1, width=xmax * 0.25)
fl.pos = (0, -1, 0)
ball = (sphere(radius=rad, pos=(px[0], py[0], 0.0), color=color.red, make_trail=True),
        sphere(radius=rad, pos=(px[1], py[1], 0.0), color=color.blue, make_trail=True))
ball[0].velocity = (v0[0] * cos(theta), v0[0] * sin(theta))
ball[1].velocity = (v0[1] * cos(theta), v0[1] * sin(theta))
# air = arrow(pos=ball[1].pos, axis=(ball[1].velocity[0] * -b, ball[1].velocity[1] * -b), shaftwidth=1)
t = 0
fin = [false, false]
scene.autoscale = false
label_velocity = (label(pos=(xmax / 2, xmax / 3, 0)),
                  label(pos=(-xmax / 2, xmax / 3, 0)))
label_velocity[1].text = "  Proyectil con resistencia  \n" \
                         "pos: (%0.2f, %0.2f)\n" % (ball[1].pos[0] - px[1], ball[1].pos[1] - py[1]) + \
                         "vel: %0.2f" % (ball[1].velocity[0] ** 2 + ball[1].velocity[1] ** 2) ** 0.5
label_velocity[0].text = "  Proyectil sin resistencia  \n" \
                         "pos: (%0.2f, %0.2f)\n" % (ball[0].pos[0] - px[0], ball[0].pos[1] - py[0]) + \
                         "vel: %0.2f" % (ball[0].velocity[0] ** 2 + ball[0].velocity[1] ** 2) ** 0.5
flytime = [0, 0]

# INICIO DEL LOOP

while ball[0].pos[1] >= py[0] or ball[1].pos[1] >= py[1]:
    rate(2000)
    if ball[1].pos[1] >= py[1]:
        aux = (next_step(lambda x, y, v: -b * v / m, t, ball[1].pos[0], ball[1].velocity[0], dt),
               next_step(lambda x, y, v: -b * v / m - g, t, ball[1].pos[1], ball[1].velocity[1], dt))
        ball[1].velocity = (aux[0][1], aux[1][1])
        ball[1].pos = (aux[0][0], aux[1][0], 0)
        # air.pos = ball[1].pos
        # air.axis = (ball[1].velocity[0] * -b, ball[1].velocity[1] * -b)
        flytime[1] = t + dt
        label_velocity[1].text = "  Proyectil con resistencia  \n" \
                                 "pos: (%0.2f, %0.2f)\n" % (ball[1].pos[0] - px[1], ball[1].pos[1] - py[1]) + \
                                 "vel: %0.2f" % (ball[1].velocity[0] ** 2 + ball[1].velocity[1] ** 2) ** 0.5
    t += dt

    if ball[0].pos[1] >= py[0]:
        ball[0].pos = (px[0] + v0[0] * cos(theta) * t,
                       py[0] + v0[0] * sin(theta) * t + (-g * t ** 2) / 2,
                       0)
        ball[0].velocity = (v0[0] * cos(theta), v0[0] * sin(theta) - g * t)
        label_velocity[0].text = "  Proyectil sin resistencia  \n" \
                                 "pos: (%0.2f, %0.2f)\n" % (ball[0].pos[0] - px[0], ball[0].pos[1] - py[0]) + \
                                 "vel: %0.2f" % (ball[0].velocity[0] ** 2 + ball[0].velocity[1] ** 2) ** 0.5
        flytime[0] = t + dt

print 'Projectile without air drag flew for: %0.2f seconds' % flytime[0]
print 'Projectile with air drag flew for: %0.2f seconds' % flytime[1]
