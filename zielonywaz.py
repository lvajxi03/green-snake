#!/usr/bin/env python

import sys
import os
import json
import random
import enum

RC_FILE = "~/.pythons-well.rc"

SUPPORTED_CHARS = "abcdefghijklmnopqrstuvwxyz" + \
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890" + \
    "!@#$%^&*()_+[]{}|<>~"

LEVEL_1= [
    "XXXXXXXXXXXXXXXXXXX@XXXXXXXXXXXXXXXXXXXX",
    "+.................. ...................+",
    "XXXX.XXXXXXXXX.XXXXXXX.XXXXXXXXXXX.XXXXX",
    "XXXX.XXXXXXXXX.XXXXXXX.XXXXXXXXXXX.XXXXX",
    "XXXX.XXXvXXXXX.XXXXXXX.XXXXXvXXXXX.XXXXX",
    "+......................................+",
    "XXXXXXXXXX.XXXXXXXXXXXXX.XXXXXXXXXX.XXXX",
    "XXXXXXXXXX.XXXXXXXXXXXXX.XXXXXXXXXX.XXXX",
    "XXXXXX%XXX.XXXXXXXXXXXXX.XXXX%XXXXX.XXXX",
    "+$...........v........................$+",
    "XXXXXX.XXXXXXXX.XXXXXXXXXX.XXXXXX.XXXXXX",
    "XXXXXX.vXXXXXXX.XXXXXXXXXX.XXXXXv.XXXXXX",
    "XXXXXX.XXXXXXXX.XXXXXX%XXX.XXXXXX.XXXXXX",
    "+..........v...................v.......+",
    "XXXXXXX.XXXXXXXXXXX.XXXXXXXXXXXXXXXX.XXX",
    "XXXXXXX.XXXXXXXXXXX.XXXXXXXXXXXXXXXX$XXX",
    "XXXXXXX.X%XXXXXXXXX.XXXXXX%XXXXXXXXX.XXX",
    "+%%................$.................%%+",
    "XXXXXXXXXXXX.XXXXXXXXXXXXXXXX.XXXXXXXXXX",
    "XXXXXXXXXXXX.XXXXXXXXXXXXXXXX.XXXXXXXXXX"]

LEVEL_2= [
    "XXXXXXXXXXXXXXXXXXX@XXXXXXXXXXXXXXXXXXXX",
    "+.................. ...................+",
    "XXXX.XXXXXXXXX.XXXXXXXXX.XXXXXXXXXX.XXXX",
    "XXXX.XXXX%vXXX.XXXXXXXXX.XXXv%XXXXX.XXXX",
    "XXXX.XXXX%XXXX.XXXXXXXXX.XXXX%XXXXX.XXXX",
    "XXXX...............$................XXXX",
    "XXXX.XXXXXXXXX.XXXXXXXXX.XXXXXXXXXX.XXXX",
    "+......................................+",
    "XXXX.XXXXX.XXXXXXXXXXXXX.XXXXXXXXXX.XXXX",
    "+$v..................................v$+",
    "XXXXXX.XXXXXXXX.XXXXXXXXXX.XXXXXX.XXXXXX",
    "XXXXXX.XXX%XXXX.XXXXXXXXXX.XXX%XX.XXXXXX",
    "XXXXXX.XXX%XXXX.XXXXXXXXXX.XXX%XX.XXXXXX",
    "XXXXXX........$..........$........XXXXXX",
    "XXXXXX.XXXXXXXXXXXX.XXXXXXXXXXXXX.XXXXXX",
    "+%vvv..............................vvv%+",
    "XXXXXX.XXXXXXXXXXXX.XXXXXX%XXXXXX.XXXXXX",
    "+%%..........v.....$........v........%%+",
    "XXXXXXXXXXXX.XXXXXXXXXXXXXXXX.XXXXXXXXXX",
    "+%%%...............$................%%%+"]

LEVEL_3= [
    "XXXXXXXXXXXXXXXXXXX@XXXXXXXXXXXXXXXXXXXX",
    "+.................. ...................+",
    "XXXXX.XXXXXXXX.XXXXXXX.XXXXXXXXXXX.XXXXX",
    "XXXXX.XXXXXXXX.XXXXXXX.XXXXXXXXXXX.XXXXX",
    "XXXXX.XXXXXXXX.XXXXXXX.XXXXXXXXXXX.XXXXX",
    "XXX.....XXXXXX%XXXXXXX%XXXXXXXXX.....XXX",
    "XXX.XXX.XXXXXXvXXXXXXXvXXXXXXXXX.XXX.XXX",
    "XXX.XXX.XX%XXXvXXXXXXXvXXXXXX%XX.XXX.XXX",
    "XXX.XXX$XX%XXXXXXXXXXXXXXXXXX%XX$XXX.XXX",
    "+%....................................%+",
    "XXXXXX.XXXXXXXX.XXXXXXXXXX.XXXXXX.XXXXXX",
    "+%....................................%+",
    "XXXXXX.XXXXXXXX.XXXXXX%XXX.XXXXXX.XXXXXX",
    "+%vvv..............................vvv%+",
    "XXXXXXX.XXXXXXXXXXX.XXXXXXXXXXXXXXXX.XXX",
    "+%%..................................%%+",
    "XXXXXXX.X%XXXXXXXXX.XXXXXX%XXXXXXXXX.XXX",
    "+%%%...............$................%%%+",
    "XXXXXXXXXXXX.XXXXXXXXXXXXXXXX.XXXXXXXXXX",
    "+$%%%%............................%%%%$+"]

LEVEL_4= [
    "XXXXXXXXXXXXXXXXXXX@XXXXXXXXXXXXXXXXXXXX",
    "+.................. ...................+",
    "XXXXXXXXXXXXXXX.XX.XX.XXXXXXXXXXXXXXXXXX",
    "+%%%%%............................%%%%%+",
    "XXXXXXXXXXXXXX.XXXXXXX.XXXXXXXXXXXXXXXXX",
    "+$....................................$+",
    "XXXXXXXXXXXXXXXXXX.XXXXXXXXXXXXXXXXXXXXX",
    "+$.....vvv................vvv.........$+",
    "XXXXXX.XXXXXXXXXXXXXXXXXXXXXX.XXXXXXXXXX",
    "+%%%%%............................%%%%%+",
    "XXXXXXXXXXXXXXXXXXX.XXXXXXXXXXXXXXXXXXXX",
    "+......................................+",
    "XXXXXXXXXXXXX.XXXXXXXX.XXXXXXXXXXXXXXXXX",
    "+.........vvv..........vvv.............+",
    "XXXXXXX.XXXXXXXXXXXXXXXXXXXXXXXXXXXX.XXX",
    "+......................................+",
    "XXXXXXXXXXXXXXXXXXX.XXXXXXXXXXXXXXXXXXXX",
    "+%%%%%.............$..............%%%%%+",
    ".XXXXXXXXXXX.XXXXXXXXXXXXXXXX.XXXXXXXXXX",
    "+$....................................$+"]

LEVEL_5= [
    "XXXXXXXXXXXXXXXXXXX@XXXXXXXXXXXXXXXXXXXX",
    "+.................. ...................+",
    "XXXXXXXXXXX.XX.XXXXXXX.XXX.XXXXXXXXXXXXX",
    "XXXXXXXXXXX.XX.X.....X.XXX.XXXXXXXXXXXXX",
    "XXXXXXXXXXX..X.XXX.XXX.XX..XXXXXXXXXXXXX",
    "XXXXXXXXXXXX.X.XXX.XXX.XX.XXXXXXXXXXXXXX",
    "XXXXXXvXXXXX.XXXXX.XXXXXX.XXXXXXXvXXXXXX",
    "XXXXXXvXXXXX.XXXXX.XXXXXX.XXXXXXXvXXXXXX",
    "XXXXXXvXXXXX.XXXXX.XXXXXX.XXXXXXXvXXXXXX",
    "+%....................................%+",
    "XXXXXXXXXXXXXXX.XXXXXXXXXX.XXXXXXXXXXXXX",
    "+%%..................................%%+",
    "XXXXXXXXXXXXXXXXXX.XXXXXXXXXXXXXXXXXXXXX",
    "+%%%................................%%%+",
    "XXXXXXXXXXXXXXXXXX.XXXXXXXXXXXXXXXXXXXXX",
    "+vvvvv............................vvvvv+",
    "XXXXXXXXXXXXXXXXXX.XXXXXXXXXXXXXXXXXXXXX",
    "+%%%%%............$...............%%%%%+",
    "XXXXXXXXXXXX.XXXXXXXXXXXXXXXX.XXXXXXXXXX",
    "+$%%%%.......vvvvvvvvvvvvvvvv.....%%%%$+"]

LEVEL_6= [
    "XXXXXXXXXXXXXXXXXXX@XXXXXXXXXXXXXXXXXXXX",
    "+..........v....... .........v.........+",
    "X.X.X.X.X.XvX.X.X.X.X.X.X.X.XvX.X.X.X.X.",
    "+$.........v.................v........$+",
    "X.X.X.X.X.XvX.X.X.X.X.X.X.X.XvX.X.X.X.X.",
    "+%%%%%%%%%%v%%%%%%%%%%%%%%%%%v%%%%%%%%%+",
    "X.X.X.X.X.XvX.X.X.X.X.X.X.X.XvX.X.X.X.X.",
    "+..........v.................v.........+",
    ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X",
    "+..........v.................v.........+",
    ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X",
    "+..........v.................v........._",
    ".X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X.X",
    "+%%%%%%%%%%v%%%%%%%%%%%%%%%%%v%%%%%%%%%+",
    "X.X.X.X.X.XvX.X.X.X.X.X.X.X.XvX.X.X.X.X.",
    "+$.........v.................v........$+",
    "X.X.X.X.X.XvX.X.X.X.X.X.X.X.XvX.X.X.X.X.",
    "+$.........v.......$.........v........$+",
    "X.X.X.X.X.XvX.X.X.X.X.X.X.X.XvX.X.X.X.X.",
    "+%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%+"]


game_levels = [
    {'title': 'LEVEL 1',
     'data': LEVEL_1},
    {'title': 'LEVEL 2',
     'data': LEVEL_2},
    {'title': 'LEVEL 3',
     'data': LEVEL_3},
    {'title': 'LEVEL 4',
     'data': LEVEL_4},
    {'title': 'LEVEL 5',
     'data': LEVEL_5},
    {'title': 'LEVEL 6',
     'data': LEVEL_6}]

@enum.unique
class Key(enum.IntEnum):
    NONE = 0
    KEY_LEFT = 1
    KEY_RIGHT = 2
    KEY_TOP = 3
    KEY_BOTTOM = 4
    KEY_ENTER = 5
    KEY_ESCAPE = 6
    KEY_BACKSPACE = 7
    KEY_SPACE = 8
    KEY_Q = 9

@enum.unique
class MouseButton(enum.IntEnum):
    NONE = 0
    LEFT = 1
    RIGHT = 2
    MIDDLE = 3
    SCROLL_UP = 4
    SCROLL_DOWN = 5


class MouseEvent():
    x = -1
    y = -1
    button = MouseButton.NONE


class Locale():

    messages = {
        'pl': {
            'new_score_msg': [
                "*** NOWY REKORD ***!",
                "",
                "GRATULACJE!",
                "TWOJ WYNIK (%SCORE%) ZOSTANIE UMIESZCZONY",
                "NA TABLICY REKORDOW!",
                "",
                "WPROWADZ SWOJE IMIE:",
                "",
                "%PLAYER%▊"],
            'gameover_msg' :[
                "UDALO CI SIE UKONCZYC TE GRE!"],
            'menu_options': [
                "NOWA GRA",
                "OPCJE",
                "TABELA REKORDOW",
                "POMOC",
                "O PROGRAMIE",
                "KONIEC"],
            'options': [
                "TRYB LATWY",
                "TRYB NORMALNY",
                "TRYB TRUDNY",
                "BRAK LIMITU CZASU"],
            'help_msg': [
                "UZYJ KLAWISZY STRZALEK DO KONTROLI WEZA",
                "ORAZ BACKSPACE DO POWROTU"
                "",
                "ZOLTE KWADRATY SA WARTE 1 PUNKT",
                "DIAMENTY SA WARTE 5 PUNKTOW",
                "NIEBIESKIE PIGULKI OPOZNIAJA POTWORY DO 20 SEKUND",
                "",
                "POTWORY NIE POWINNY DOTKNAC WEZA",
                "CZERWONA PIGULKA NIE POWINNA DOTKNAC GLOWY",
                "",
                "POWODZENIA! BEDZIE CI POTRZEBNE!"],
            'help_header': '*** POMOC ***',
            'about_header': '*** O PROGRAMIE ***',
            'gameover_header': "*** GRATULACJE ***",
            'about_msg': [
                "PYTHON'S WELL:",
                "GRA POSWIECONA ORYGINALNEJ *OIL`S WELL*",
                "(C) THOMAS J. MITCHELL, 1993",
                "",
                "NAPISANA JAKO CWICZENIE W PYQT",
                "(Marcin Bielewicz, 2020)"],
            'ctrl_line': "(uzyj , ESC albo Q aby opuscic ten ekran)",
            'gameover_ctrl_line': "(nacisnij dowolny klawisz, aby kontynuowac)",
            'high_scores_header': "*** TABELA REKORDOW ***",
            'new_score_header': "*** NOWY REKORD ***",
            'options_header': '*** USTAWIENIA ***',
            'time_score': "CZAS: %03d PUNKTY: %04d",
            'score': "PUNKTY: %04d",
            'game_paused': " GRA WSTRZYMANA",
            'continue': "NACISNIJ SPACJE BY KONTYNUOWAC",
            'game_over': 'KONIEC GRY!',
            'press_q': 'NACISNIJ Q BY ZAKONCZYC',
            'press_space': 'NACISNIJ SPACJE BY ROZPOCZAC'},
        'en': {
            'new_score_msg': [
                "*** NEW HIGH SCORE ***",
                "",
                "CONGRATULATIONS!",
                "YOUR SCORE (%SCORE%) WILL NOW BE PRESENT",
                "ON THE SCORE TABLE!",
                "",
                "PLEASE ENTER YOUR NAME:",
                "",
                "%PLAYER%▊"],
            'gameover_msg' :[
                "YOU HAVE JUST COMPLETED THIS GAME!"],
            'menu_options': [
                "NEW GAME",
                "OPTIONS",
                "HIGH SCORES",
                "HELP",
                "ABOUT",
                "QUIT"],
            'options': [
                "EASY MODE",
                "NORMAL MODE",
                "HARDCORE MODE",
                "NO TIME LIMIT"],
            'help_msg': [
                "USE ARROW KEYS TO CONTROL THE SNAKE",
                "AND BACKSPACE FOR IMMEDIATE RETURN",
                "",
                "YELLOW SQUARE IS WORTH 1 POINT",
                "DIAMOND IS WORTH 5 POINTS",
                "BLUE PILLS SLOW MONSTERS FOR 20 SECONDS",
                "",
                "MONSTER SHOULD NOT HIT SNAKE BODY",
                "RED PILL SHOULD NOT TOUCH ITS HEAD",
                "",
                "GOOD LUCK! YOU WILL NEED IT!"],
            'help_header': "*** HELP ***",
            'about_header': "*** ABOUT THIS GAME ***",
            'gameover_header': "*** CONGRATULATIONS ***",
            'about_msg': [
                "PYTHON'S WELL:",
                "A TRIBUTE TO ORIGINAL *OIL'S WELL*",
                "BY THOMAS J. MITCHELL, 1993",
                "",
                "WRITTEN TO PRACTISE PYQT",
                "(Marcin Bielewicz, 2020)"],
            'ctrl_line': "(use , ESC or Q to leave this screen)",
            'gameover_ctrl_line': "(press any key to continue)",
            'high_scores_header': "*** HIGH SCORES ***",
            'new_score_header': "*** NEW HIGH SCORE ***",
            'options_header': '*** OPTIONS ***',
            'time_score': "TIME: %03d SCORE: %04d",
            'score': "SCORE: %04d",
            'game_paused': " GAME PAUSED",
            'continue': "PRESS SPACE TO CONTINUE",
            'game_over': "GAME OVER!",
            'press_q': "PRESS Q TO CONTINUE",
            'press_space': "PRESS SPACE WHEN READY"}}

    @staticmethod
    def get(lang, key):
        if lang in Locale.messages:
            if key in Locale.messages[lang]:
                return Locale.messages[lang][key]
        return None

SCREEN_WIDTH=1200
SCREEN_HEIGHT=700

BOARD_WIDTH=1200
BOARD_HEIGHT=600

BLOCK_WIDTH = 30
BLOCK_HEIGHT = 30


@enum.unique
class Move(enum.IntEnum):
    RIGHT = enum.auto()
    BOTTOM = enum.auto()
    LEFT = enum.auto()
    TOP = enum.auto()


@enum.unique
class MonsterDirection(enum.IntEnum):
    EAST = 0
    WEST = 1


@enum.unique
class Orientation(enum.IntEnum):
    HORIZONTAL = 0
    VERTICAL = 1
    NW = enum.auto()
    SW = enum.auto()
    NE = enum.auto()
    SE = enum.auto()


@enum.unique
class GameBoard(enum.IntEnum):
    UNKNOWN = 0
    WELCOME = 1
    MENU = 2
    GAME = 3
    OPTIONS = 4
    PAUSE = 5
    HISCORES = 6
    NEWSCORE = 7
    HELP = 8
    ABOUT = 9
    QUIT  = 10
    LANGPL = 11
    LANGEN = 12
    GAMEOVER = 13


@enum.unique
class GameState(enum.IntEnum):
    UNKNOWN = 0
    INITIALIZED = 1
    STARTED = 2
    PAUSED = 3
    COLLIDED = 4
    FROZEN = 5
    GAMEOVER = 6


@enum.unique
class MenuOption(enum.IntEnum):
    NEWGAME = 0
    OPTIONS = 1
    HISCORES = 2
    HELP = 3
    ABOUT = 4
    QUIT = 5


@enum.unique
class GameMode(enum.IntEnum):
    EASY = 0
    NORMAL = 1
    HARD = 2
    UNLIMITED = 3


class Sword():
    def __init__(self, x, y, pic):
        self.x = x
        self.y = y
        self.real_x = x * BLOCK_WIDTH
        self.real_y = 100 + y * BLOCK_HEIGHT
        self.pixmap = pic
        self.width = pic.width()
        self.height = pic.height()

    def __repr__(self):
        return "<S>(%(a)d, %(b)d)" % {
            'a': self.x,
            'b': self.y}


class Rect():
    x = -1
    y = -1
    w = -1
    h = -1

    def __init__(self,
                 x: int,
                 y: int,
                 w: int,
                 h: int):
        self.x = x
        self.y = y
        self.w = w
        self.h = h

    def __repr__(self):
        return "<Rect>((%(x)d, %(y)d) => (%(xx)d, %(yy)d)[%(w)dx%(h)d])" % {
            'x': self.x,
            'y': self.y,
            'xx': self.x + self.w,
            'yy': self.y + self.h,
            'w': self.w,
            'h': self.h}

    def belongs(self,
                x: int,
                y: int):
        if x >= self.x and x <= self.x + self.w:
            if y >= self.y and y <= self.y + self.h:
                return True
        return False


class Configuration():
    '''
    Game configuration aspects
    '''
    container = {}

    def __init__(self, cfg_file: str =  None):
        self.cfg_file = cfg_file
        if cfg_file:
            try:
                fh = open(cfg_file)
                js = json.load(fh)
                fh.close()
                self.container = js
                self.cfg_file = cfg_file
            except FileNotFoundError:
                pass
            except json.decoder.JSONDecodeError:
                pass
        self.align()
        self.cleanup_scores()

    def get_lang(self):
        return self.container['lang']

    def set_lang(self, lang):
        self.container['lang'] = lang

    def align(self):
        '''
        Validate configuration entries
        '''
        if 'hiscores' not in self.container:
            self.container['hiscores'] = []
        if 'lang' not in self.container:
            self.container['lang'] = 'pl'
        if 'mode' not in self.container:
            self.container['mode'] = GameMode.EASY
        if self.container['mode'] < GameMode.EASY:
            self.container['mode'] = GameMode.EASY
        if self.container['mode'] > GameMode.UNLIMITED:
            self.container['mode'] = GameMode.UNLIMITED

    def lowest_score(self):
        '''
        Return lowest score from hiscores
        '''
        hsc = self.container['hiscores']
        self.cleanup_scores()
        if len(self.container['hiscores']) > 0:
            lowest = 1000000
        else:
            lowest = 0
        for score in hsc:
            (n, s) = score
            if s < lowest:
                lowest = s
        return lowest

    def cleanup_scores(self):
        s = []
        if 'hiscores' in self.container:
            for sc in self.container['hiscores']:
                (n, w) = sc
                if w > 0:
                    s.append(sc)
        s.sort(key=lambda tup: tup[1], reverse=True)
        self.container['hiscores'] = s[:15] if len(s) > 15 else s

    def append_score(self, name, score):
        lowest = self.lowest_score()
        self.cleanup_scores()
        hsc = self.container['hiscores']
        if score > lowest:
            f = (name, score)
            hsc.append(f)
            hsc.sort(key=lambda tup: tup[1], reverse=True)
            if len(hsc) > 15:
                self.container['hiscores'] = hsc[:15]

    def get_scores(self):
        return self.container['hiscores']

    def get_mode(self):
        return self.container['mode']

    def set_mode(self, mode):
        if mode >= GameMode.EASY and mode <= GameMode.UNLIMITED:
            self.container['mode'] = mode

    def save(self, cfg_file=None):
        if not cfg_file:
            if self.cfg_file:
                cfg_file = self.cfg_file
        self.cleanup_scores()
        try:
            fh = open(cfg_file, "w")
            s = json.dumps(self.container)
            fh.write(s)
            fh.close()
        except  IOError as ioe:
            pass


# utils.cc: collide
def collide(head, monster):
    x = head.x * BLOCK_HEIGHT
    y = head.y * BLOCK_HEIGHT + 100
    if x >= monster.real_x + monster.width:
        return False
    if  monster.real_x >= x + BLOCK_WIDTH:
        return False
    if y >= monster.real_y + monster.height:
        return False
    if  monster.real_y >= y + BLOCK_HEIGHT:
        return False
    return True


# monster.cc: class Monster
class Monster():
    def __init__(self, x, y, pixmap, max_speed=3):
        self.x = x
        self.y = y
        self.real_x = x * BLOCK_WIDTH
        self.real_y = 100 + y * BLOCK_HEIGHT
        if self.x == 0:
            self.direction = MonsterDirection.WEST
        else:
            self.direction =  MonsterDirection.EAST
        self.pixmap = pixmap
        self.width = 40
        self.height = 20
        self.speed = random.randint(1, max_speed)

    def __repr__(self):
        return "<M>(%(a)d, %(b)d => %(c)d)" % {
            'a': self.x,
            'b': self.y,
            'c': self.direction}

class Killer():
    def __init__(self, x, y, pixmaps, max_speed=3):
        self.x = x
        self.y = y
        self.real_x = x * BLOCK_WIDTH
        self.real_y = 100 + y * BLOCK_HEIGHT
        if self.x == 0:
            self.direction = MonsterDirection.WEST
            self.pixmaps = pixmaps['right']
        else:
            self.direction =  MonsterDirection.EAST
            self.pixmaps = pixmaps['left']
        self.width = 40
        self.height = 22
        self.speed = 5 #? random.randint(1, max_speed)

    def __repr__(self):
        return "<F>(%(a)d, %(b)d => %(c)d)" % {
            'a': self.x,
            'b': self.y,
            'c': self.direction}


class Game():
    def __init__(self, canvas, arena, configuration):
        self.arena = arena
        self.configuration = configuration
        self.game_state = GameState.UNKNOWN
        self.level_index = 0
        self.max_level_index = len(game_levels)
        self.player = ""
        self.swords = []
        self.killers = []
        self.swords_consumed = 0
        self.title = "PYTHON'S WELL"
        self.collision_counter = 0
        self.board = GameBoard.MENU
        self.canvas = canvas
        self.counter = 180
        self.monsters = []
        self.snake = None
        self.lives = 3
        self.score = 0
        self.option_selected = 0
        self.option = 0
        self.freeze_counter = 0
        self.to_pick = 0
        try:
            self.maxset = len(self.get_msg('options')) - 1
        except TypeError:
            self.maxset = 0
        # Timers
        self.arena.timers['tick-event'].timeout.connect(
            self.tick_event)
        self.arena.timers['counter-event'].timeout.connect(
            self.counter_event)
        self.arena.timers['collision-event'].timeout.connect(
            self.collision_event)
        self.arena.timers['consume-event'].timeout.connect(
            self.consume_event)
        self.arena.timers['freeze-event'].timeout.connect(
            self.freeze_event)
        # Painters
        self.painters = {
            GameBoard.GAMEOVER: self.paint_gameover,
            GameBoard.NEWSCORE: self.paint_newscore,
            GameBoard.OPTIONS: self.paint_options,
            GameBoard.HELP: self.paint_help,
            GameBoard.GAME: self.paint_game,
            GameBoard.MENU: self.paint_menu,
            GameBoard.ABOUT: self.paint_about,
            GameBoard.HISCORES: self.paint_hiscores}

    # game.cc: void Game::notify_pick
    def notify_pick(self):
        self.score += 1
        self.arena.media_play_pick()
        self.to_pick -= 1

    # game.cc: void Game::notify_fireball
    def notify_fireball(self):
        self.score += 3
        self.arena.media_play_diamond()
        self.to_pick -= 1
        if self.is_unlimited():
            x, y = random.choice(self.level.entry_points)
            self.create_sword(
                x,
                y,
                self.arena.media['sword-fire'])

    # game.cc: void Game::notify_diamond
    def notify_diamond(self):
        self.score += 5
        self.to_pick -= 1
        self.arena.media_play_diamond()

    # game.cc: void Game::notify_freeze
    def notify_freeze(self):
        self.to_pick -= 1
        self.arena.media_play_freeze()
        if not self.is_frozen():
            # Clear killers list.
            # No idea if killers should be frozen, or freely go,
            # or just disappear.
            self.killers = []
            self.change_state(GameState.FROZEN)

    # game.cc: void Game::next_level
    def next_level(self):
        if self.level_index < len(game_levels) - 1:
            self.level_index += 1
            self.level = Level(game_levels[self.level_index]['data'])
            self.to_pick = self.level.to_pick
            self.snake = Snake(self, self.level)
            if not self.is_unlimited():
                self.counter = 180 + 60 * self.level_index
            else:
                self.counter = 999
            self.monsters = []
            self.create_monsters()
            self.start_game()
            self.game_state = GameState.INITIALIZED
        else:
            self.stop_game()
            self.change_board(GameBoard.GAMEOVER)
        self.paint()

    # game.cc: void Game::game_initialize
    def game_initialize(self):
        self.level = Level(game_levels[self.level_index]['data'])
        self.snake = Snake(self, self.level)
        self.to_pick = self.level.to_pick
        if not self.is_unlimited():
            self.counter = 180 + 60 * self.level_index
        else:
            self.counter = 999
        self.swords = []
        self.swords_consumed = 0
        self.score = 0
        self.lives = 3
        self.monsters = []
        self.create_monsters()

    # game.cc: void Game::change_state
    def change_state(self, state):
        if self.game_state != state:
            self.game_state = state
            # Necessary actions should be triggered below:
            if state == GameState.INITIALIZED:
                self.game_initialize()
            elif state == GameState.STARTED:
                self.start_game()
            elif state == GameState.PAUSED:
                self.pause_game()
            elif state == GameState.COLLIDED:
                self.stop_game()
            elif state == GameState.GAMEOVER:
                self.stop_game()
            elif state == GameState.FROZEN:
                self.freeze_game()
        self.paint()

    # game.cc: Monster *Game::create_monster
    def create_monster(self, x, y):
        if self.is_unlimited():
            speed = 3 + self.level_index
        else:
            speed = 3 + self.level_index + self.configuration.get_mode()

        return Monster(
            x, y,
            random.choice(self.arena.media['creatures']),
            speed)

    #game.cc: void Game::event_tick(
    def tick_event(self):
        head = self.snake.blocks[-1]
        rest = self.snake.blocks[:-1]
        collided = False
        for f in self.killers:
            # Killers are dangerous for snake's head only.
            # This is to prevent player from moving in first
            # line on the board only.
            if collide(head, f):
                if not self.is_unlimited() and not self.is_frozen():
                    collided = True
                    self.change_state(GameState.COLLIDED)
                    self.arena.media_play_snake()
                    if self.collision_counter  == 0:
                        self.collision_counter = 6
                        self.paint(inverted=True)
                        self.arena.timers[
                            'collision-event'].start(200)
                if self.is_unlimited():
                    if self.is_frozen():
                        # WTF?! Skad m?!
                        x = int(m.real_x/BLOCK_HEIGHT)
                        self.create_sword(
                            x,
                            m.y,
                            self.arena.media['sword-ice'])
        for s in self.swords:
            if collide(head, s):
                try:
                    self.swords.remove(s)
                    self.swords_consumed += 1
                    self.arena.media_play_eat()
                except ValueError:
                    pass

        for m in self.monsters:
            if collide(head, m):
                try:
                    self.monsters.remove(m)
                    self.score += 2
                    self.arena.media_play_eat()
                except ValueError:
                    pass
            else:
                for r in rest:
                    if not collided:
                        if collide(r, m):
                            if not self.is_unlimited() and not self.is_frozen():
                                collided = True
                                self.change_state(GameState.COLLIDED)
                                self.arena.media_play_snake()
                                if self.collision_counter  == 0:
                                    self.collision_counter = 6
                                    self.paint(inverted=True)
                                    self.arena.timers[
                                        'collision-event'].start(200)
                            if self.is_unlimited():
                                if self.is_frozen():
                                    # Create sword _in place_ of monster hit:
                                    x = int(m.real_x/BLOCK_HEIGHT)
                                    self.create_sword(
                                        x,
                                        m.y,
                                        self.arena.media['sword-ice'])
                                self.arena.media_play_snake()
                                self.change_state(GameState.COLLIDED)
                                collided = True
                                self.paint(inverted=True)
                                self.arena.timers[
                                    'collision-event'].start(200)
                            return
            if not self.is_frozen() or self.is_unlimited():
                if m.direction == MonsterDirection.WEST:
                    m.real_x += m.speed
                    if m.real_x > self.canvas.w + m.width:
                        try:
                            self.monsters.remove(m)
                        except ValueError:
                            pass
                        m = self.create_monster(m.x,  m.y)
                        self.monsters.append(m)
                else:
                    m.real_x -= m.speed
                    if m.real_x < -m.width:
                        try:
                            self.monsters.remove(m)
                        except ValueError:
                            pass
                        m = self.create_monster(m.x,  m.y)
                        self.monsters.append(m)
        for f in self.killers:
            if f.direction == MonsterDirection.WEST:
                f.real_x += f.speed
                if f.real_x > self.canvas.w + f.width:
                    try:
                        self.killers.remove(f)
                    except ValueError:
                        pass
            else:
                f.real_x -= f.speed
                if f.real_x < -f.width:
                    try:
                        self.killers.remove(f)
                    except ValueError:
                        pass
        self.paint()
        if self.to_pick == 0:
            if self.counter > 0:
                self.stop_game()
                self.next_level()
        elif self.lives == 0:
            self.stop.game()
            self.change_state(GameState.GAMEOVER)

    # game.cc: bool Game::is_unlimited
    def is_unlimited(self):
        return self.configuration.get_mode() == GameMode.UNLIMITED

    # void Game::event_freeze
    def freeze_event(self):
        if not self.is_unlimited():
            self.freeze_counter -= 1
            if self.freeze_counter == 0:
                self.arena.timers[
                    'freeze-event'].stop()
                self.game_state = GameState.STARTED
                self.arena.timers[
                    'counter-event'].start(1000)

    # game.cc: void Game::update_monsters
    def update_monsters(self):
        if len(self.monsters) < int(len(self.level.entry_points)/2):
            pick = []
            for ep in self.level.entry_points:
                iss = False
                for m in self.monsters:
                    (x, y) = ep
                    if m.x == x and m.y == y:
                        iss = True
                if not iss:
                    pick.append(ep)
            for i in range(0, int(len(pick)/2)):
                ep = random.choice(pick)
                x, y = ep
                m = self.create_monster(x, y)
                pick.remove(ep)
                self.monsters.append(m)

    # game.cc: void Game::create_killer
    def create_killer(self):
        if len(self.killers) == 0:
            if self.is_unlimited():
                speed = 3 + self.level_index
            else:
                speed = 3 + self.level_index + self.configuration.get_mode()
            points = self.level.entry_points[0:2]
            x, y = random.choice(points)
            self.killers.append(
                Killer(x,
                         y,
                         self.arena.media['killers'],
                         speed))

    # game.cc: void Game::event_counter
    def counter_event(self):
        self.counter -= 1
        if self.counter % 10 == 0:
            self.update_monsters()
        if self.counter % 24 == 0:
            self.create_killer()
        if not self.is_unlimited():
            if self.counter == 0:
                self.stop_game()
                self.change_state(GameState.GAMEOVER)
        else:
            if self.counter < 0:
                self.counter = 999

    def paint(self, **kwargs):
        self.painters[self.board](**kwargs)

    def paint_gameover(self, **kwargs):
        data = {
            'header': self.get_msg('gameover_header'),
            'msg': self.get_msg('gameover_msg'),
            'ctrl_line': self.get_msg('gameover_ctrl_line')}
        self.canvas.paint_gameover(data)

    def paint_newscore(self, **kwargs):
        help_msg = self.get_msg('new_score_msg')
        c = [m.replace(
            '%SCORE%', '%(s)d' % {
                's': self.score}) for m in help_msg]
        c = [m.replace('%PLAYER%', self.player) for m in c]
        data = {
            'msg': c,
            'ctrl_line': self.get_msg('ctrl_line')}
        self.canvas.paint_newscore(data)

    def paint_options(self, **kwargs):
        data = {
            'options-header': self.get_msg('options_header'),
            'options': self.get_msg('options'),
            'option': self.option}
        self.canvas.paint_options(data)

    def paint_game(self, **kwargs):
        '''
        A painter for game mode
        '''
        inverted = kwargs.pop('inverted', False)
        data = {
            'level': self.level.level,
            'monsters': self.monsters,
            'killers': self.killers,
            'freeze-counter': self.freeze_counter,
            'swords': self.swords,
            'snake-blocks': self.snake.blocks,
            'is-frozen': self.is_frozen(),
            'score': self.score,
            'is-paused': self.is_paused(),
            'is-over': self.is_over(),
            'is-initialized': self.is_initialized(),
            'lives': self.lives,
            'counter': self.counter,
            'mode': self.configuration.get_mode(),
            'level-index': self.level_index,
            'time-score': self.get_msg('time_score'),
            'swords-consumed': self.swords_consumed,
            'game-paused': self.get_msg('game_paused'),
            'continue': self.get_msg('continue'),
            'press-q': self.get_msg('press_q'),
            'press-space': self.get_msg('press_space'),
            'game-over': self.get_msg('game_over'),
            'score-msg': self.get_msg('score')}
        self.canvas.paint_game(data, inverted=inverted)

    def paint_menu(self, **kwargs):
        data = {
            'title': self.title,
            'options': self.get_msg('menu_options'),
            'option-selected': self.option_selected}
        self.canvas.paint_menu(data)

    # game.cc: void Game::create_monsters
    def create_monsters(self):
        self.monsters = []
        for ep in self.level.entry_points:
            x, y = ep
            m = self.create_monster(x, y)
            self.monsters.append(m)
        self.killers = []

    # game.cc: void Game::event_consume
    def consume_event(self):
        if not self.snake.consume():
            self.arena.timers[
                'consume-event'].stop()
            self.monsters = []
            self.create_monsters()
            if not self.is_unlimited():
                self.lives -= 1 if self.lives > 0 else 0
                if self.lives == 0:
                    self.change_state(GameState.GAMEOVER)
                else:
                    self.run_game()
            else:
                self.run_game()
        else:
            self.arena.media_play_consume()
            self.paint(inverted=True)

    def create_sword(self, x, y, pic):
        s = Sword(x, y, pic)
        self.swords.append(s)

    # game.cc: void Game::event_collision
    def collision_event(self):
        if self.collision_counter > 0:
            f = self.collision_counter % 2
            self.paint(inverted=(f > 0))
            self.collision_counter -= 1
        else:
            self.arena.timers['collision-event'].stop()
            self.arena.timers['consume-event'].start(100)

    def start_game(self, inverted = False):
        for timer in self.arena.timers:
            self.arena.timers[timer].stop()
        self.freeze_counter = 0

    # game.cc: void Game::run_game
    def run_game(self):
        self.game_state = GameState.STARTED
        self.arena.timers['tick-event'].start(40)
        self.arena.timers['counter-event'].start(1000)

    # game.cc: void Game::pause_game
    def pause_game(self):
        self.arena.timers['tick-event'].stop()
        self.arena.timers['counter-event'].stop
        self.paint()

    def stop_game(self):
        for timer in self.arena.timers:
            self.arena.timers[timer].stop()
        self.paint()

    def freeze_game(self):
        self.freeze_counter = 20
        self.arena.timers['counter-event'].stop()
        self.arena.timers['freeze-event'].start(1000)

    def paint_help(self, **kwargs):
        data = {
            'header': self.get_msg('help_header'),
            'msg': self.get_msg('help_msg'),
            'ctrl_line': self.get_msg('ctrl_line')}
        self.canvas.paint_help(data)

    def paint_hiscores(self, **kwargs):
        scores = self.configuration.get_scores()
        l = len(scores)
        for i in range(15-l):
            scores.append(("---", 0))
        data = {
            'header': self.get_msg('high_scores_header'),
            'scores': scores,
            'ctrl_line': self.get_msg('ctrl_line')}
        self.canvas.paint_hiscores(data)

    def paint_about(self, **kwargs):
        data = {
            'header': self.get_msg('about_header'),
            'about_msg': self.get_msg('about_msg'),
            'ctrl_line': self.get_msg('ctrl_line')}
        self.canvas.paint_about(data)

    def quit(self):
        self.configuration.save()
        sys.exit(0)

    def move_right(self):
        self.snake.move_right()

    def move_left(self):
        self.snake.move_left()

    def move_up(self):
        self.snake.move_up()

    def move_down(self):
        self.snake.move_down()

    def move_back(self):
        self.snake.consume()

    def change_board(self, board):
        self.level_index = 0
        self.board = board
        if board == GameBoard.QUIT:
            self.quit()
        elif board == GameBoard.MENU:
            self.stop_game()
        elif board == GameBoard.GAME:
            self.change_state(GameState.INITIALIZED)
        elif board == GameBoard.LANGPL:
            self.configuration.set_lang('pl')
            self.change_board(GameBoard.MENU)
        elif board == GameBoard.LANGEN:
            self.configuration.set_lang('en')
            self.change_board(GameBoard.MENU)
        elif board == GameBoard.OPTIONS:
            self.option = self.configuration.get_mode()
        self.paint()

    def keypressed_menu(self, key, text):
        options = self.get_msg('menu_options')
        maxopt = len(options) - 1
        if key == Key.KEY_TOP:
            self.option_selected -= 0 if self.option_selected == 0 else 1
        elif key == Key.KEY_BOTTOM:
            self.option_selected += 0 if self.option_selected == maxopt else 1
        elif key == Key.KEY_ENTER:
            if self.option_selected == MenuOption.NEWGAME:
                self.change_board(GameBoard.GAME)
            elif self.option_selected == MenuOption.OPTIONS:
                self.change_board(GameBoard.OPTIONS)
            elif self.option_selected == MenuOption.HISCORES:
                self.change_board(GameBoard.HISCORES)
            elif self.option_selected == MenuOption.HELP:
                self.change_board(GameBoard.HELP)
            elif self.option_selected == MenuOption.ABOUT:
                self.change_board(GameBoard.ABOUT)
            elif self.option_selected == MenuOption.QUIT:
                self.change_board(GameBoard.QUIT)
        elif key == Key.KEY_Q:
            self.change_board(GameBoard.QUIT)
        self.paint()

    def is_started(self):
        return self.game_state == GameState.STARTED

    def is_paused(self):
        return self.game_state == GameState.PAUSED

    def is_over(self):
        return self.game_state == GameState.GAMEOVER

    def is_initialized(self):
        return self.game_state == GameState.INITIALIZED

    def is_frozen(self):
        return self.game_state == GameState.FROZEN

    def keypressed_newhiscore(self, key, text):
        if text in SUPPORTED_CHARS:
            self.player += text
        if key == Key.KEY_LEFT:
            self.change_board(GameBoard.MENU)
        elif key == Key.KEY_ESCAPE:
            self.change_board(GameBoard.MENU)
        elif key == Key.KEY_BACKSPACE:
            if len(self.player) > 0:
                self.player = self.player[:-1]
        elif key == Key.KEY_ENTER:
            if self.player:
                self.configuration.append_score(self.player, self.score)
            self.change_board(GameBoard.HISCORES)
        self.paint()

    def get_msg(self, id: str) -> str:
        lang = self.configuration.get_lang()
        return Locale.get(lang, id)

    def keypressed_game(self, key: Key, text: str):
        if key == Key.KEY_LEFT:
            if self.is_started() or self.is_frozen():
                self.move_left()
        elif key == Key.KEY_RIGHT:
            if self.is_started() or self.is_frozen():
                self.move_right()
        elif key == Key.KEY_TOP:
            if self.is_started() or self.is_frozen():
                self.move_up()
        elif key == Key.KEY_BOTTOM:
            if self.is_started() or self.is_frozen():
                self.move_down()
        elif key == Key.KEY_SPACE:
            if self.is_initialized() or self.is_paused():
                self.change_state(GameState.STARTED)
                self.run_game()
        elif key == Key.KEY_ESCAPE:
            if self.is_started():
                self.change_state(GameState.PAUSED)
        elif key == Key.KEY_Q:
            if self.game_state == GameState.GAMEOVER:
                lowest = self.configuration.lowest_score()
                if self.score > lowest:
                    self.change_board(GameBoard.NEWSCORE)
                else:
                    self.change_board(GameBoard.MENU)
            else:
                self.change_board(GameBoard.MENU)
        elif key == Key.KEY_BACKSPACE:
            if self.is_started() or self.is_frozen():
                self.move_back()

    def keypressed_options(self, key, text):
        if key == Key.KEY_TOP:
            self.option -= 0 if self.option == 0 else 1
        elif key == Key.KEY_BOTTOM:
            self.option += 0 if self.option == self.maxset else 1
        elif key == Key.KEY_ENTER:
            self.configuration.set_mode(self.option)
            self.change_board(GameBoard.MENU)
        elif key == Key.KEY_ESCAPE:
            self.change_board(GameBoard.MENU)
        elif key == Key.KEY_LEFT:
            self.change_board(GameBoard.MENU)
        elif key == Key.KEY_Q:
            self.change_board(GameBoard.MENU)
        self.paint()

    def keypressed_gameover(self, key, text):
        if self.score > self.configuration.lowest_score():
            self.change_board(GameBoard.NEWSCORE)
        else:
            self.change_board(GameBoard.MENU)

    def keypressed(self, key, text):
        if self.board == GameBoard.MENU:
            self.keypressed_menu(key, text)
        elif self.board == GameBoard.GAME:
            self.keypressed_game(key, text)
        elif self.board == GameBoard.OPTIONS:
            self.keypressed_options(key, text)
        elif self.board == GameBoard.ABOUT:
            self.keypressed_about(key, text)
        elif self.board == GameBoard.HELP:
            self.keypressed_help(key, text)
        elif self.board == GameBoard.HISCORES:
            self.keypressed_hiscores(key, text)
        elif self.board == GameBoard.NEWSCORE:
            self.keypressed_newhiscore(key, text)
        elif self.board == GameBoard.GAMEOVER:
            self.keypressed_gameover(key, text)

    def mouse_pressed(self, event):
        if self.board == GameBoard.GAME:
            self.mouse_pressed_game(event)
        elif self.board == GameBoard.MENU:
            self.mouse_pressed_menu(event)
        elif self.board == GameBoard.HISCORES:
            self.mouse_pressed_hiscores(event)
        elif self.board == GameBoard.NEWSCORE:
            self.mouse_pressed_newscore(event)
        elif self.board == GameBoard.HELP:
            self.mouse_pressed_help(event)
        elif self.board == GameBoard.ABOUT:
            self.mouse_pressed_about(event)
        elif self.board == GameBoard.OPTIONS:
            self.mouse_pressed_options(event)

    def mouse_pressed_options(self, event):
        for region in self.arena.options_regions:
            if region.belongs(event.x, event.y):
                self.configuration.set_mode(self.arena.options_regions[region])
                self.change_board(GameBoard.MENU)

    def mouse_pressed_menu(self, event: MouseEvent):
        for region in self.arena.menu_regions:
            if region.belongs(event.x, event.y):
                self.change_board(self.arena.menu_regions[region])

    def mouse_pressed_game(self, event):
        if self.game_state == GameState.STARTED:
            self.change_state(GameState.PAUSED)
        elif self.game_state == GameState.PAUSED:
            self.change_state(GameState.STARTED)
            self.run_game()

    def mouse_pressed_help(self, event):
        self.change_board(GameBoard.MENU)

    def mouse_pressed_hiscores(self, event):
        self.change_board(GameBoard.MENU)

    def mouse_pressed_newscore(self, event):
        self.change_board(GameBoard.MENU)

    def mouse_pressed_about(self, event):
        self.change_board(GameBoard.MENU)

    def keypressed_about(self, key, text):
        if key == Key.KEY_LEFT:
            self.change_board(GameBoard.MENU)
        elif key == Key.KEY_ESCAPE:
            self.change_board(GameBoard.MENU)
        elif key == Key.KEY_Q:
            self.change_board(GameBoard.MENU)

    def keypressed_help(self, key, text):
        if key == Key.KEY_LEFT:
            self.change_board(GameBoard.MENU)
        elif key == Key.KEY_ESCAPE:
            self.change_board(GameBoard.MENU)
        elif key == Key.KEY_Q:
            self.change_board(GameBoard.MENU)

    def keypressed_hiscores(self, key, text):
        if key == Key.KEY_LEFT:
            self.change_board(GameBoard.MENU)
        elif key == Key.KEY_ESCAPE:
            self.change_board(GameBoard.MENU)
        elif key == Key.KEY_Q:
            self.change_board(GameBoard.MENU)


class SnakeBlock():
    def __init__(self, x, y, head):
        self.x = x
        self.y = y
        self.head = head
        self.orientation = Orientation.VERTICAL

        def __repr__(self):
            return "<B>(%(x)d, %(y)d)" % {
                'x': self.x,
                'y': self.y}


def get_orientation(p, c, n):
    # FROM HERE
    if p.orientation == Orientation.NE:
        if n.head == Move.BOTTOM:
            c.orientation = Orientation.SW
        elif n.head == Move.LEFT:
            c.orientation = Orientation.SW
        elif n.head == Move.RIGHT:
            c.orientation = Orientation.HORIZONTAL
        elif n.head == Move.TOP:
            c.orientation = Orientation.VERTICAL
    elif p.orientation == Orientation.NW:
        if n.head == Move.BOTTOM:
            c.orientation = Orientation.SE
        elif n.head == Move.RIGHT:
            c.orientation = Orientation.SE
        elif n.head == Move.LEFT:
            c.orientation = Orientation.HORIZONTAL
        elif n.head == Move.TOP:
            c.orientation = Orientation.VERTICAL
    elif p.orientation == Orientation.SW:
        if n.head == Move.RIGHT:
            c.orientation = Orientation.NE
        elif n.head == Move.TOP:
            c.orientation = Orientation.NE
        elif n.head == Move.LEFT:
            c.orientation = Orientation.HORIZONTAL
        elif n.head == Move.BOTTOM:
            c.orientation = Orientation.VERTICAL
    elif p.orientation == Orientation.SE:
        if n.head == Move.LEFT:
            c.orientation = Orientation.NW
        elif n.head == Move.TOP:
            c.orientation = Orientation.NW
        elif n.head == Move.RIGHT:
            c.orientation = Orientation.HORIZONTAL
    # TO HERE
    elif p.head == Move.RIGHT:
        if n.head == Move.RIGHT:
            c.orientation = Orientation.HORIZONTAL
        elif n.head == Move.TOP:
            if p.orientation == Orientation.NW:
                c.orientation = Orientation.VERTICAL
            else:
                c.orientation = Orientation.NW
        elif n.head == Move.BOTTOM:
            if p.orientation == Orientation.SW:
                c.orientation = Orientation.VERTICAL
            else:
                c.orientation = Orientation.SW
    elif p.head == Move.LEFT:
        if n.head == Move.LEFT:
            c.orientation = Orientation.HORIZONTAL
        elif n.head == Move.TOP:
            if p.orientation == Orientation.NE:
                c.orientation = Orientation.VERTICAL
            else:
                c.orientation = Orientation.NE
        elif n.head == Move.BOTTOM:
            if p.orientation == Orientation.SE:
                c.orientation = Orientation.VERTICAL
            else:
                c.orientation = Orientation.SE
    elif p.head == Move.BOTTOM:
        if n.head == Move.BOTTOM:
            c.orientation = Orientation.VERTICAL
        elif n.head == Move.LEFT:
            if p.orientation == Orientation.NW:
                c.orientation = Orientation.HORIZONTAL
            else:
                c.orientation = Orientation.NW
        elif n.head == Move.RIGHT:
            if p.orientation == Orientation.NE:
                c.orientation = Orientation.HORIZONTAL
            else:
                c.orientation = Orientation.NE
    elif p.head == Move.TOP:
        if n.head == Move.TOP:
            c.orientation = Orientation.VERTICAL
        elif n.head == Move.RIGHT:
            if p.orientation == Orientation.SE:
                c.orientation = Orientation.HORIZONTAL
            else:
                c.orientation = Orientation.SE
        elif n.head == Move.LEFT:
            if p.orientation == Orientation.SW:
                c.orientation = Orientation.HORIZONTAL
            else:
                c.orientation = Orientation.SW
    return c.orientation


class Level():
    def __init__(self, level):
        self.level = []
        self.to_pick = 0
        self.entry_points = []
        i = 0
        j = 0
        for line in level:
            row = []
            i = 0
            for char in line:
                if char == '@':
                    self.spot_x = i
                    self.spot_y = j
                    row.append(char)
                elif char == '+':
                    self.entry_points.append((i, j))
                    row.append('.')
                    self.to_pick += 1
                elif char in ['.', '$', '%', 'v']:
                    self.to_pick += 1
                    row.append(char)
                else:
                    row.append(char)
                i += 1
            self.level.append(row)
            j += 1

    def get_at(self, x, y):
        return self.level[y][x]

    def set_at(self, x, y, c):
        self.level[y][x] = c


class Snake():
    def __init__(self, game, level):
        self.level = level
        self.blocks = []
        self.game = game
        self.spot_x = self.level.spot_x
        self.spot_y = self.level.spot_y
        b = SnakeBlock(self.spot_x, self.spot_y, Move.BOTTOM)
        self.blocks.append(b)
        b = SnakeBlock(self.spot_x, self.spot_y+1, Move.BOTTOM)
        self.blocks.append(b)
        self.x = self.spot_x
        self.y = self.spot_y+1

    def __repr__(self):
        r = "<S>[~:%(x)d, %(y)d]" % {
            'x': self.spot_x,
            'y': self.spot_y}
        for b in self.blocks:
            r += str(b)
        r += "[@:%(x)d, %(y)d]" % {
            'x': self.x,
            'y': self.y
            }
        return r

    # snake.cc: bool Snake::has_prev
    def has_prev(self, x, y):
        try:
            b = self.blocks[-2]
            if b.x == x and b.y == y:
                return True
        except IndexError:
            return False

    # snake.cc: bool Snake::contains
    def contains(self, x: int, y: int):
        for b in self.blocks:
            if b.x == x and b.y == y:
                return True
        return False

    # snake.cc: bool Snake::consume
    def consume(self):
        if len(self.blocks) > 2:
            self.blocks = self.blocks[:-1:]
            b = self.blocks[-1]
            self.x = b.x
            self.y = b.y
            return True
        return False

    # snake.cc: void Snake::move
    def move(self, direction):
        try:
            if direction == Move.RIGHT:
                next_x = self.x+1
                next_y = self.y
            elif direction == Move.BOTTOM:
                next_x = self.x
                next_y = self.y+1
            elif direction == Move.LEFT:
                next_x = self.x-1
                next_y = self.y
            elif direction == Move.TOP:
                next_x = self.x
                next_y = self.y-1
            h = self.level.get_at(next_x, next_y)
            if next_x < 0:
                return
            if next_x > len(self.level.level[0]):
                return
            if next_y < 0:
                return
            if next_y > len(self.level.level):
                return
            if self.has_prev(next_x, next_y):
                self.consume()
            elif self.contains(next_x, next_y):
                return
            elif h != 'X':
                self.x = next_x
                self.y = next_y
                if h == '.':
                    self.level.set_at(self.x, self.y, ' ')
                    self.game.notify_pick()
                elif h == 'v':
                    self.level.set_at(self.x, self.y, ' ')
                    self.game.notify_fireball()
                elif h == '%':
                    self.level.set_at(self.x, self.y, ' ')
                    self.game.notify_diamond()
                elif h == '$':
                    self.level.set_at(self.x, self.y, ' ')
                    self.game.notify_freeze()
                b = SnakeBlock(self.x, self.y, direction)
                self.blocks.append(b)
        except IndexError:
            pass

    def move_right(self):
        self.move(Move.RIGHT)

    def move_left(self):
        self.move(Move.LEFT)

    def move_up(self):
        self.move(Move.TOP)

    def move_down(self):
        self.move(Move.BOTTOM)
