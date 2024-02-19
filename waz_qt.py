#!/usr/bin/env python

try:
    from PySide2.QtWidgets import QApplication
    from PySide2.QtWidgets import QMainWindow
    from PySide2.QtWidgets import QLabel

    from PySide2.QtGui import QPixmap
    from PySide2.QtGui import QPainter
    from PySide2.QtGui import QFont
    from PySide2.QtGui import QFontMetrics
    from PySide2.QtGui import QColor
    from PySide2.QtGui import QBrush
    from PySide2.QtGui import QPen

    from PySide2.QtMultimedia import QSound

    from PySide2.QtCore import QSize
    from PySide2.QtCore import QTimer

    from PySide2.QtCore import Qt

except ImportError:
    from PyQt5.QtWidgets import QApplication
    from PyQt5.QtWidgets import QMainWindow
    from PyQt5.QtWidgets import QLabel

    from PyQt5.QtGui import QPixmap
    from PyQt5.QtGui import QImage
    from PyQt5.QtGui import QPainter
    from PyQt5.QtGui import QFont
    from PyQt5.QtGui import QFontMetrics
    from PyQt5.QtGui import QColor
    from PyQt5.QtGui import qRgb
    from PyQt5.QtGui import qRed
    from PyQt5.QtGui import QBrush
    from PyQt5.QtGui import QPen

    from PyQt5.QtMultimedia import QSound

    from PyQt5.QtCore import QSize
    from PyQt5.QtCore import QTimer

    from PyQt5.QtCore import Qt

from zielonywaz import *

class Canvas(QLabel):
    def __init__(self, parent, w, h, arena):
        super().__init__(parent)
        self.w = w
        self.h = h
        self.font = QFont("C64 Pro", 18)
        self.fm = QFontMetrics(self.font)
        ph = self.fm.height()
        self.h += ph + 8
        self.arena = arena

    def sizeHint(self):
        return QSize(
            self.w,
            self.h)

    def get_pipes(self, frozen, inverted=False):
        if inverted:
            return self.arena.media['pipes']['inverted']
        elif frozen:
            return self.arena.media['pipes']['frozen']
        return self.arena.media['pipes']['normal']

    def get_heads(self, frozen, inverted=False):
        if inverted:
            return self.arena.media['heads']['inverted']
        elif frozen:
            return self.arena.media['heads']['frozen']
        return self.arena.media['heads']['normal']

    def paint_options(self, data, **kwargs):
        pi = QPixmap(
            self.w,
            self.h)
        pi.fill(QColor("#232323"))
        pa = QPainter()
        pa.begin(pi)
        pa.setPen(QPen(QColor("#979797"), 2, Qt.SolidLine))
        pa.setBrush(QBrush(QColor("#979797"), Qt.SolidPattern))
        pa.setFont(self.font)
        text = data['options-header']
        x = int((SCREEN_WIDTH - self.fm.width(text))/2)
        pa.drawText(x, 80, text)
        i = 0
        for opt in data['options']:
            if i == data['option']:
                pa.setPen(QPen(QColor("#aac13c"), 2, Qt.SolidLine))
                pa.setBrush(QBrush(QColor("#0f4480"), Qt.SolidPattern))
            else:
                pa.setPen(QPen(QColor("#232323"), 2, Qt.SolidLine))
                pa.setBrush(QBrush(QColor("#979797"), Qt.SolidPattern))
            x = int((SCREEN_WIDTH - self.fm.width(opt))/2)
            y = int(40 + self.fm.height()/2)
            pa.drawRect(300, 120 * (i+1), 600, 80)
            pa.drawText(x, 120 * (i+1) + y, opt)
            i += 1
        pa.end()
        self.setPixmap(pi)

    def paint_menu(self, data, **kwargs):
        pi = QPixmap(
            self.w,
            self.h)
        pi.fill(QColor("#232323"))
        pa = QPainter()
        pa.begin(pi)
        pa.setPen(QPen(QColor("#979797"), 2, Qt.SolidLine))
        pa.setBrush(QBrush(QColor("#979797"), Qt.SolidPattern))
        pa.setFont(self.font)
        text = data['title']
        x = int((SCREEN_WIDTH - self.fm.width(text))/2)
        pa.drawText(x, 80, text)
        i = 0
        for opt in data['options']:
            if i == data['option-selected']:
                pa.setPen(QPen(QColor("#aac13c"), 2, Qt.SolidLine))
                pa.setBrush(QBrush(QColor("#0f4480"), Qt.SolidPattern))
            else:
                pa.setPen(QPen(QColor("#232323"), 2, Qt.SolidLine))
                pa.setBrush(QBrush(QColor("#979797"), Qt.SolidPattern))
            x = int((SCREEN_WIDTH - self.fm.width(opt))/2)
            y = int(40 + self.fm.height()/2)
            pa.drawRect(300, 100 * (i+1), 600, 80)
            pa.drawText(x, 100 * (i+1) + y, opt)
            i += 1
            pa.drawPixmap(
                self.w-80,
                self.h-24,
                self.arena.media['flags']['pl'])
            pa.drawPixmap(
                self.w-38,
                self.h-24,
                self.arena.media['flags']['en'])
        pa.end()
        self.setPixmap(pi)

    def paint_game(self, data, **kwargs):
        inverted = kwargs.pop('inverted', False)
        pi = QPixmap(
            self.w,
            self.h)
        counter = data['counter']
        pi.fill(QColor("#232323"))
        pa = QPainter()
        pa.begin(pi)
        pa.setFont(self.font)
        pa.drawPixmap(
            0,
            0,
            self.w,
            100,
            self.arena.media['top-image'])
        i = 0
        for line in data['level']:
            j = 0
            for char in line:
                c = None
                if char == 'X':
                    if data['is-frozen']:
                        c = self.arena.media['block']['frozen']
                    else:
                        c = self.arena.media['block']['normal']
                elif char == '%':
                    c = self.arena.media['diamonds'][counter % 4]
                elif char == '$':
                    c = self.arena.media['freezes'][counter % 4]
                elif char == '.':
                    c = self.arena.media['squares'][counter % 4]
                elif char == 'v':
                    c = self.arena.media['fire-balls'][counter % 4]
                if c:
                    pa.drawPixmap(
                        j * BLOCK_WIDTH,
                        100+i * BLOCK_HEIGHT,
                        BLOCK_WIDTH,
                        BLOCK_HEIGHT,
                        c)
                j += 1
            i += 1
        blocks = data['snake-blocks']
        f = len(blocks)
        pipes = self.get_pipes(data['is-frozen'], inverted)
        heads = self.get_heads(data['is-frozen'], inverted)
        for i in range(f):
            e = None
            block = blocks[i]
            if i == 0:
                e = pipes[1]
            else:
                try:
                    p = blocks[i-1]
                    n = blocks[i+1]
                    g = get_orientation(p, block, n)
                    f = int(g)
                    e = pipes[f]
                except IndexError:
                    if i == 0:
                        e = pipes[1]
                    elif block.head == Move.BOTTOM:
                        e = heads['bottom']
                    elif block.head == Move.TOP:
                        e = heads['top']
                    elif block.head == Move.RIGHT:
                        e = heads['right']
                    elif block.head == Move.LEFT:
                        e = heads['left']
            pa.drawPixmap(
                block.x * BLOCK_WIDTH,
                100+block.y * BLOCK_HEIGHT,
                BLOCK_WIDTH,
                BLOCK_HEIGHT,
                e)
        for s in data['swords']:
            pa.drawPixmap(
                s.real_x,
                s.real_y,
                31,
                30,
                s.pixmap)
        for m in data['monsters']:
            pa.drawPixmap(
                m.real_x,
                m.real_y + 3,
                40,
                22,
                m.pixmap if not data[
                    'is-frozen'] else self.arena.media[
                    'frozen-creature'])
        for f in data['killers']:
            pa.drawPixmap(
                f.real_x,
                f.real_y + 3,
                40,
                22,
                f.pixmaps['normal' if f.real_x %2 == 0 else 'bright'])
        pa.setPen(QColor("#b8b8b8"))
        text = game_levels[data['level-index']]['title'] + " " + \
            "❤" * data['lives']
        if data['mode'] != GameMode.UNLIMITED:
            text += " " + data['time-score'] % (
                data['counter'],
                data['score'])
            if data['is-frozen']:
                text += " | " + "%(s)d" % {'s': data['freeze-counter']}
        else:
            text += " " + data['score-msg'] % (data['score'])
        pa.drawText(
            4,
            self.h-4,
            text)
        if data['swords-consumed'] > 0:
            pa.drawPixmap(
                1120,
                SCREEN_HEIGHT,
                31,
                30,
                self.arena.media['sword-ice'])
            pa.drawText(
                1152,
                self.h-4,
                "%(f)d" % {'f': data['swords-consumed']})
        if data['is-paused']:
            pa.setPen(QPen(QColor("#880000"), 5, Qt.SolidLine))
            pa.setBrush(QBrush(QColor("#979797"), Qt.SolidPattern))
            pa.drawRect(250, 200, 700, 200)
            pa.setFont(self.font)
            pa.setPen(QPen(QColor("#880000"), 1, Qt.SolidLine))
            text = data['game-paused']
            x = int((SCREEN_WIDTH - self.fm.width(text))/2)
            pa.drawText(x, 290, text)
            text = data['continue']
            x = int((SCREEN_WIDTH - self.fm.width(text))/2)
            pa.drawText(x, 340, text)
        if data['is-over']:
            pa.setPen(QPen(QColor("#880000"), 5, Qt.SolidLine))
            pa.setBrush(QBrush(QColor("#979797"), Qt.SolidPattern))
            pa.drawRect(250, 200, 700, 200)
            pa.setFont(self.font)
            pa.setPen(QPen(QColor("#880000"), 1, Qt.SolidLine))
            text = data['game-over']
            x = int((SCREEN_WIDTH - self.fm.width(text))/2)
            pa.drawText(x, 290, text)
            text = data['press-q']
            x = int((SCREEN_WIDTH - self.fm.width(text))/2)
            pa.drawText(x, 340, text)
        if data['is-initialized']:
            pa.setPen(QPen(QColor("#880000"), 5, Qt.SolidLine))
            pa.setBrush(QBrush(QColor("#979797"), Qt.SolidPattern))
            pa.drawRect(250, 200, 700, 200)
            pa.setFont(self.font)
            pa.setPen(QPen(QColor("#880000"), 1, Qt.SolidLine))
            text = data['press-space']
            x = int((SCREEN_WIDTH - self.fm.width(text))/2)
            pa.drawText(x, 310, text)
        pa.end()
        self.setPixmap(pi)

    def paint_gameover(self, data, **kwargs):
        pi = QPixmap(
            self.w,
            self.h)
        pi.fill(QColor("#7c70da"))
        pa = QPainter()
        pa.begin(pi)
        pa.setPen(QPen(QColor("#3e31a2"), 2, Qt.SolidLine))
        pa.setBrush(QBrush(QColor("#3e31a2"), Qt.SolidPattern))
        pa.drawRect(50, 50, self.w-100, self.h-150)
        pa.setFont(self.font)
        pa.setPen(QPen(QColor("#7c70da"), 2, Qt.SolidLine))
        r = 0
        text = data['header']
        x = int((SCREEN_WIDTH - self.fm.width(text))/2)
        pa.drawText(x, 74, text)
        gmsg = data['msg']
        for msg in gmsg:
            x = int((SCREEN_WIDTH - self.fm.width(msg))/2)
            pa.drawText(x, 150 + r*70, msg)
            r += 1
        pa.setPen(QPen(QColor("#3e31a2"), 2, Qt.SolidLine))
        text = data['ctrl_line']
        x = int((SCREEN_WIDTH - self.fm.width(text))/2)
        pa.drawText(
            x,
            self.h-24,
            text)
        pa.end()
        self.setPixmap(pi)

    def paint_help(self, data, **kwargs):
        pi = QPixmap(
            self.w,
            self.h)
        pi.fill(QColor("#7c70da"))
        pa = QPainter()
        pa.begin(pi)
        pa.setPen(QPen(QColor("#3e31a2"), 2, Qt.SolidLine))
        pa.setBrush(QBrush(QColor("#3e31a2"), Qt.SolidPattern))
        pa.drawRect(50, 50, self.w-100, self.h-150)
        pa.setFont(self.font)
        pa.setPen(QPen(QColor("#7c70da"), 2, Qt.SolidLine))
        text = data['header']
        x = int((SCREEN_WIDTH - self.fm.width(text))/2)
        pa.drawText(x, 74, text)
        r = 0
        help_msg = data['msg']
        pixmaps = [
            None,
            None,
            None,
            self.arena.media['squares'][0],
            self.arena.media['diamonds'][0],
            self.arena.media['freezes'][0],
            None,
            self.arena.media['creatures'][6],
            self.arena.media['killers']['right']['normal'],
            None,
            None]
        for msg in help_msg:
            pa.drawText(200, 150 + r*40, msg)
            if pixmaps[r]:
                pa.drawPixmap(
                    140,
                    125 + r*40, pixmaps[r])
            r += 1

        pa.setPen(QPen(QColor("#3e31a2"), 2, Qt.SolidLine))
        text = data['ctrl_line']
        x = int((SCREEN_WIDTH - self.fm.width(text))/2)
        pa.drawText(
            x,
            self.h-24,
            text)
        pa.end()

        self.setPixmap(pi)

    def paint_hiscores(self, data, **kwargs):
        pi = QPixmap(
            self.w,
            self.h)
        pi.fill(QColor("#7c70da"))
        pa = QPainter()
        pa.begin(pi)
        pa.setPen(QPen(QColor("#3e31a2"), 2, Qt.SolidLine))
        pa.setBrush(QBrush(QColor("#3e31a2"), Qt.SolidPattern))
        pa.drawRect(50, 50, self.w-100, self.h-150)
        pa.setFont(self.font)
        pa.setPen(QPen(QColor("#7c70da"), 2, Qt.SolidLine))
        r = 0
        text = data['header']
        x = int((SCREEN_WIDTH - self.fm.width(text))/2)
        pa.drawText(x, 74, text)
        for score in data['scores']:
            name, s = score
            pa.drawText(70, 120 + r*35, "%02d." % (r+1))
            pa.drawText(160, 120 + r*35, "%04d" % (s) + " " + name)
            r += 1
        pa.setPen(QPen(QColor("#3e31a2"), 2, Qt.SolidLine))
        text = data['ctrl_line']
        x = int((SCREEN_WIDTH - self.fm.width(text))/2)
        pa.drawText(
            x,
            self.h-24,
            text)
        pa.end()
        self.setPixmap(pi)

    def paint_about(self, data, **kwargs):
        pi = QPixmap(
            self.w,
            self.h)
        pi.fill(QColor("#7c70da"))
        pa = QPainter()
        pa.begin(pi)
        pa.setPen(QPen(QColor("#3e31a2"), 2, Qt.SolidLine))
        pa.setBrush(QBrush(QColor("#3e31a2"), Qt.SolidPattern))
        pa.drawRect(50, 50, self.w-100, self.h-150)
        pa.setFont(self.font)
        pa.setPen(QPen(QColor("#7c70da"), 2, Qt.SolidLine))
        r = 0
        header = data['header']
        x = int((SCREEN_WIDTH - self.fm.width(header))/2)
        pa.drawText(x, 74, header)
        about_msg = data['about_msg']
        for msg in about_msg:
            x = int((SCREEN_WIDTH - self.fm.width(msg))/2)
            pa.drawText(x, 150 + r*70, msg)
            r += 1
        pa.setPen(QPen(QColor("#3e31a2"), 2, Qt.SolidLine))
        text = data['ctrl_line']
        x = int((SCREEN_WIDTH - self.fm.width(text))/2)
        pa.drawText(
            x,
            self.h-24,
            text)
        pa.end()
        self.setPixmap(pi)

    def paint_newscore(self, data, **kwargs):
        pi = QPixmap(
            self.w,
            self.h)

        pi.fill(QColor("#7c70da"))
        pa = QPainter()
        pa.begin(pi)
        pa.setPen(QPen(QColor("#3e31a2"), 2, Qt.SolidLine))
        pa.setBrush(QBrush(QColor("#3e31a2"), Qt.SolidPattern))
        pa.drawRect(50, 50, self.w-100, self.h-150)
        pa.setFont(self.font)
        pa.setPen(QPen(QColor("#7c70da"), 2, Qt.SolidLine))
        r = 0
        for msg in data['msg']:
            x = int((SCREEN_WIDTH - self.fm.width(msg))/2)
            pa.drawText(x, 150 + r*40, msg)
            r += 1
        pa.setPen(QPen(QColor("#3e31a2"), 2, Qt.SolidLine))
        text = data['ctrl_line']
        x = int((SCREEN_WIDTH - self.fm.width(text))/2)
        pa.drawText(
            x,
            self.h-24,
            text)
        pa.end()
        self.setPixmap(pi)

        def eventFilter(self, source, event):
            if event.type() == QEvent.MouseMove:
                if event.buttons() == Qt.NoButton:
                    pos = event.pos()
                    print("YYY")
                    print (pos.x(), pos.y())
        

class Controller(QMainWindow):
    def __init__(self, parent):
        super().__init__()
        self.parent = parent
        self.setWindowTitle("Python's Well")
        self.setMouseTracking(True)

        def eventFilter(self, source, event):
            if event.type() == QEvent.MouseMove:
                if event.buttons() == Qt.NoButton:
                    pos = event.pos()
                    print (pos.x(), pos.y())

    def keyPressEvent(self, event):
        key = event.key()
        text = event.text()
        k = self.parent.keymapping.get(key, None)
        self.game.keypressed(k, text)

    def mousePressEvent(self, event):
        pos = event.pos()
        k = MouseEvent()
        k.x, k.y = pos.x(), pos.y()
        self.game.mouse_pressed(k)

class Arena(QApplication):
    def __init__(self, args: list):
        super().__init__(args)
        self.keymapping = {
            Qt.Key_Left: Key.KEY_LEFT,
            Qt.Key_Right: Key.KEY_RIGHT,
            Qt.Key_Up: Key.KEY_TOP,
            Qt.Key_Down: Key.KEY_BOTTOM,
            Qt.Key_Enter: Key.KEY_ENTER,
            Qt.Key_Return: Key.KEY_ENTER,
            Qt.Key_Escape: Key.KEY_ESCAPE,
            Qt.Key_Backspace: Key.KEY_BACKSPACE,
            81: Key.KEY_Q,
            32: Key.KEY_SPACE}

        self.menu_regions = {
            Rect(300, 100, 600, 80): GameBoard.GAME,
            Rect(300, 200, 600, 80): GameBoard.OPTIONS,
            Rect(300, 300, 600, 80): GameBoard.HISCORES,
            Rect(300, 400, 600, 80): GameBoard.HELP,
            Rect(300, 500, 600, 80): GameBoard.ABOUT,
            Rect(300, 600, 600, 80): GameBoard.QUIT,
            Rect(1124, 710, 33, 18): GameBoard.LANGPL,
            Rect(1166, 710, 33, 18): GameBoard.LANGEN}

        self.options_regions = {
            Rect(300, 120, 600, 80): GameMode.EASY,
            Rect(300, 240, 600, 80): GameMode.NORMAL,
            Rect(300, 360, 600, 80): GameMode.HARD,
            Rect(300, 480, 600, 80): GameMode.UNLIMITED}

        self.timers = {
            'tick-event': QTimer(),
            'counter-event': QTimer(),
            'collision-event': QTimer(),
            'consume-event': QTimer(),
            'freeze-event': QTimer()}
        self.media = {
            'sounds': {
                'coin': QSound('sounds/coin.wav'),
                'pipe': QSound('sounds/pipe.wav'),
                'pop': QSound('sounds/pop.wav'),
                'splat': QSound('sounds/splat.wav'),
                'stab': QSound('sounds/stab.wav'),
                'snake': QSound('sounds/snake.wav'),
                'swoosh': QSound('sounds/swoosh.wav')},
            'creatures': [
                QPixmap("images/creature-1.png"),
                QPixmap("images/creature-2.png"),
                QPixmap("images/creature-3.png"),
                QPixmap("images/creature-4.png"),
                QPixmap("images/creature-5.png"),
                QPixmap("images/creature-6.png"),
                QPixmap("images/creature-7.png")],
            'pipes': {
                'normal': [
                    QPixmap("images/pipe-horizontal.jpg"),
                    QPixmap("images/pipe-vertical.jpg"),
                    QPixmap("images/pipe-nw.jpg"),
                    QPixmap("images/pipe-sw.jpg"),
                    QPixmap("images/pipe-ne.jpg"),
                    QPixmap("images/pipe-se.jpg")],
                'inverted':[
                    QPixmap("images/pipe-horizontal-inverted.jpg"),
                    QPixmap("images/pipe-vertical-inverted.jpg"),
                    QPixmap("images/pipe-nw-inverted.jpg"),
                    QPixmap("images/pipe-sw-inverted.jpg"),
                    QPixmap("images/pipe-ne-inverted.jpg"),
                    QPixmap("images/pipe-se-inverted.jpg")],
                'frozen':[
                    QPixmap("images/pipe-horizontal-frozen.jpg"),
                    QPixmap("images/pipe-vertical-frozen.jpg"),
                    QPixmap("images/pipe-nw-frozen.jpg"),
                    QPixmap("images/pipe-sw-frozen.jpg"),
                    QPixmap("images/pipe-ne-frozen.jpg"),
                    QPixmap("images/pipe-se-frozen.jpg")]},
            'heads': {
                'normal': {
                    "bottom": QPixmap("images/head-bottom.jpg"),
                    "top": QPixmap("images/head-top.jpg"),
                    "left": QPixmap("images/head-left.jpg"),
                    "right": QPixmap("images/head-right.jpg")},
                'inverted': {
                    "bottom": QPixmap("images/head-bottom-inverted.jpg"),
                    "top": QPixmap("images/head-top-inverted.jpg"),
                    "left": QPixmap("images/head-left-inverted.jpg"),
                    "right": QPixmap("images/head-right-inverted.jpg")},
                'frozen': {
                    "bottom": QPixmap("images/head-bottom-frozen.jpg"),
                    "top": QPixmap("images/head-top-frozen.jpg"),
                    "left": QPixmap("images/head-left-frozen.jpg"),
                    "right": QPixmap("images/head-right-frozen.jpg")}},
            'freezes': [
                QPixmap("images/freeze-1.jpg"),
                QPixmap("images/freeze-2.jpg"),
                QPixmap("images/freeze-3.jpg"),
                QPixmap("images/freeze-4.jpg")],
            'diamonds': [
                QPixmap("images/diamond1.jpg"),
                QPixmap("images/diamond2.jpg"),
                QPixmap("images/diamond3.jpg"),
                QPixmap("images/diamond4.jpg")],
            'squares': [
                QPixmap("images/square-1.jpg"),
                QPixmap("images/square-2.jpg"),
                QPixmap("images/square-3.jpg"),
                QPixmap("images/square-4.jpg")],
            'block': {
                'normal': QPixmap("images/block.jpg"),
                'frozen': QPixmap('images/frozen-block.jpg')},
            'flags': {
                'pl': QPixmap("images/pl_flag.jpg"),
                'en': QPixmap("images/en_flag.jpg")},
            'top-image': QPixmap("images/top-1.jpg"),
            'frozen-creature': QPixmap("images/frozen-creature.png"),
            'sword-fire': QPixmap("images/sword-fire.png"),
            'sword-ice': QPixmap("images/sword-ice.png"),
            'fireball': QPixmap("images/fireball.png"),
            'fire-balls': [
                QPixmap("images/fire-ball-1.png"),
                QPixmap("images/fire-ball-2.png"),
                QPixmap("images/fire-ball-3.png"),
                QPixmap("images/fire-ball-4.png")],
            'killers': {
                'right': {
                    'normal': QPixmap("images/killer-right.png"),
                    'bright': QPixmap("images/killer-right-bright.png"),
                    },
                'left': {
                    'normal': QPixmap("images/killer-left.png"),
                    'bright': QPixmap("images/killer-left-bright.png")}}
        }

    def media_play_consume(self):
        self.media['sounds']['swoosh'].play()

    def media_play_pick(self):
        self.media['sounds']['pop'].play()

    def media_play_diamond(self):
        self.media['sounds']['coin'].play()

    def media_play_freeze(self):
        self.media['sounds']['pipe'].play()

    def media_play_snake(self):
        self.media['sounds']['snake'].play()

    def media_play_eat(self):
        self.media['sounds']['stab'].play()

if __name__ == "__main__":
    random.seed()
    arena = Arena(sys.argv)
    window = Controller(arena)
    arena.installEventFilter(window)
    canvas = Canvas(window, SCREEN_WIDTH, SCREEN_HEIGHT, arena)
    arena.installEventFilter(canvas)
    cfg_file = os.path.expanduser(RC_FILE)
    configuration = Configuration(cfg_file)
    game = Game(canvas, arena, configuration)
    game.paint()
    window.game = game
    window.setCentralWidget(canvas)
    window.show()
    sys.exit(arena.exec_())
