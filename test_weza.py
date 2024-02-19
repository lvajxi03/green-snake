#!/usr/bin/env python

from zielonywaz import *

import pytest

import os
import json
import sys

from unittest.mock import MagicMock
from unittest.mock import patch

CFG_FILE="config.file"

def teardown_function():
    if os.path.exists(CFG_FILE):
        os.unlink(CFG_FILE)

def test_rect_belongs_1():
    rect = Rect(10, 10, 100, 100)
    result = rect.belongs(50, 50)
    assert result == True

def test_rect_belongs_2():
    rect = Rect(10, 10, 100, 100)
    result = rect.belongs(150, 150)
    assert result == False

def test_rect_belongs_3():
    rect = Rect(10, 10, 100, 100)
    rect2 = Rect(40, 40, 100, 100)
    result = rect.belongs(100, 100)
    assert result == True
    result = rect2.belongs(100, 100)
    assert result == True

def test_rect_repr_1():
    rect = Rect(10, 10, 100, 100)
    s = str(rect)
    assert s == "<Rect>((10, 10) => (110, 110)[100x100])"

def test_level_1():
    LEVEL = ["XXXX",
             "X..X",
             "X..X"]
    l = Level(LEVEL)
    assert l.get_at(1, 1) == '.'

def test_level_2():
    LEVEL = ["XX@X",
             "X..X",
             "+..+"]
    l = Level(LEVEL)
    assert len(l.entry_points) == 2

def test_configuration_1():
    with pytest.raises(OSError) as ei:
        c = Configuration('/dev/watchdog')

def test_configuration_2():
    t = {'this': 3, 'other': None}
    fh = open(CFG_FILE, 'w')
    fh.write(json.dumps(t))
    fh.close()
    c = Configuration(CFG_FILE)
    assert 'lang' in c.container
    assert c.get_lang() == 'pl'

def test_configuration_3():
    t = {'lang': 'de', 'other': None}
    fh = open(CFG_FILE, 'w')
    fh.write(json.dumps(t))
    fh.close()
    c = Configuration(CFG_FILE)
    assert 'lang' in c.container
    assert c.get_lang() == 'de'

def test_configuration_4():
    t = {'lang': 'de', 'other': None}
    fh = open(CFG_FILE, 'w')
    fh.write(json.dumps(t))
    fh.close()
    c = Configuration(CFG_FILE)
    assert 'hiscores' in c.container
    assert len(c.container['hiscores']) == 0

def test_configuration_5():
    t = {'lang': 'de', 'other': None}
    fh = open(CFG_FILE, 'w')
    fh.write(json.dumps(t))
    fh.close()
    c = Configuration(CFG_FILE)
    for i in range(0, 20):
        c.container['hiscores'].append(('TC_5', 0))
    c.cleanup_scores()
    assert len(c.container['hiscores']) == 0

def test_configuration_6():
    t = {'lang': 'de', 'other': None}
    fh = open(CFG_FILE, 'w')
    fh.write(json.dumps(t))
    fh.close()
    c = Configuration(CFG_FILE)
    for i in range(0, 20):
        c.container['hiscores'].append(('TC_6', i))
    c.cleanup_scores()
    assert len(c.container['hiscores']) == 15

def test_configuration_7():
    t = {'lang': 'de', 'other': None}
    fh = open(CFG_FILE, 'w')
    fh.write(json.dumps(t))
    fh.close()
    c = Configuration(CFG_FILE)
    c.set_lang('cz')
    assert 'cz' == c.container['lang']

def test_configuration_8():
    t = {'lang': 'de', 'other': None}
    fh = open(CFG_FILE, 'w')
    fh.write(json.dumps(t))
    fh.close()
    c = Configuration(CFG_FILE)
    for i in range(0, 20):
        c.append_score('TC_8', i)
    assert c.lowest_score() == 5

def test_configuration_9():
    t = {'lang': 'de', 'other': None}
    fh = open(CFG_FILE, 'w')
    fh.write(json.dumps(t))
    fh.close()
    c = Configuration(CFG_FILE)
    for i in range(100, 200):
        c.append_score('TC_9', i)
    c.append_score('Me, myself and i', 150)
    assert c.lowest_score() == 185

def test_configuration_10():
    t = {'lang': 'de', 'other': None}
    fh = open(CFG_FILE, 'w')
    fh.write(json.dumps(t))
    fh.close()
    c = Configuration(CFG_FILE)
    for i in range(100, 110):
        c.append_score('TC_10', i)
    c.append_score('Me, myself and i', 150)
    assert c.lowest_score() == 100
    assert len(c.get_scores()) == 11

def test_configuration_11():
    t = {'lang': 'de', 'other': None}
    fh = open(CFG_FILE, 'w')
    fh.write(json.dumps(t))
    fh.close()
    c = Configuration(CFG_FILE)
    assert c.lowest_score() == 0
    assert len(c.get_scores()) == 0
    c.append_score('A', 1)
    c.append_score('A', 2)
    c.append_score('A', 3)
    c.save(CFG_FILE)
    d = Configuration(CFG_FILE)
    assert len(d.get_scores()) == 3

def test_configuration_13():
    d = Configuration('/etc/passwd')
    assert d.container['mode'] == GameMode.EASY

def test_configuration_14():
    t = {'mode': 2}
    fh = open(CFG_FILE, 'w')
    fh.write(json.dumps(t))
    fh.close()
    c = Configuration(CFG_FILE)
    assert c.container['mode'] == GameMode.HARD

def test_configuration_15():
    t = {'mode': 5}
    fh = open(CFG_FILE, 'w')
    fh.write(json.dumps(t))
    fh.close()
    c = Configuration(CFG_FILE)
    assert c.container['mode'] == GameMode.UNLIMITED

def test_configuration_16():
    t = {'mode': 5}
    fh = open(CFG_FILE, 'w')
    fh.write(json.dumps(t))
    fh.close()
    c = Configuration(CFG_FILE)
    c.save(CFG_FILE)
    d = Configuration(CFG_FILE)
    assert d.container['mode'] == GameMode.UNLIMITED

def test_configuration_17():
    c = Configuration('/dev/null')
    c.set_mode(8)
    assert c.container['mode'] == GameMode.EASY

def test_configuration_18():
    c = Configuration('/dev/null')
    c.set_mode(-2)
    assert c.get_mode() == GameMode.EASY

def test_configuration_19():
    c = Configuration('/dev/null')
    c.set_mode(2)
    assert c.get_mode() == GameMode.HARD

def test_configuration_20():
    c = Configuration('/dev/null')
    c.container['mode'] = -2
    c.align()
    assert c.get_mode() == GameMode.EASY

def test_configuration_21():
    c = Configuration('/dev/null')
    c.container['mode'] = 70
    c.align()
    assert c.get_mode() == GameMode.UNLIMITED

def test_configuration_22():
    c = Configuration('=234=234=234=234=234=')
    c.container['mode'] = 70
    c.align()
    assert c.get_mode() == GameMode.UNLIMITED

def test_configuration_23():
    with patch.object(json, 'dumps', return_value=None) as espresso:
        with pytest.raises(TypeError) as ei:
            c = Configuration()
            c.save()
        espresso.assert_not_called()

def test_configuration_24():
    with patch.object(json, 'dumps', return_value=None) as espresso:
        with pytest.raises(TypeError) as ei:
            c = Configuration(CFG_FILE)
            c.save()
        espresso.assert_called()

def test_collide_1():
    m = MagicMock()
    m.width = MagicMock(return_value=38)
    m.height = MagicMock(return_value=30)
    h = SnakeBlock(0, 0, Move.BOTTOM)
    n = Monster(0, 0, m, 1)
    assert collide(h, n) == True

def test_collide_2():
    m = MagicMock()
    m.width = MagicMock(return_value=38)
    m.height = MagicMock(return_value=30)
    h = SnakeBlock(0, 0, Move.BOTTOM)
    n = Monster(5, 5, m, 1)
    assert collide(h, n) == False

def test_collide_3():
    m = MagicMock()
    m.width = MagicMock(return_value=38)
    m.height = MagicMock(return_value=30)
    h = SnakeBlock(70, 0, Move.BOTTOM)
    n = Monster(0, 0, m, 1)
    assert collide(h, n) == False

def test_collide_4():
    n = MagicMock()
    n.width = MagicMock(return_value=38)
    n.height = MagicMock(return_value=30)
    h = SnakeBlock(0, 70, Move.BOTTOM)
    m = Monster(0, 0, n, 1)
    assert collide(h, m) == False

def test_collide_5():
    m = MagicMock()
    m.width = MagicMock(return_value=38)
    m.height = MagicMock(return_value=30)
    h = SnakeBlock(0, 0, Move.BOTTOM)
    n = Monster(0, 70, m, 1)
    assert collide(h, n) == False

def test_monster_1():
    m = MagicMock()
    m.width = MagicMock(return_value=38)
    m.height = MagicMock(return_value=30)
    n = Monster(0, 5, m, 1)
    assert str(n) == "<M>(0, 5 => 1)"

def test_monster_2():
    m = MagicMock()
    m.width = MagicMock(return_value=38)
    m.height = MagicMock(return_value=30)
    n = Monster(6, 5, m, 1)
    assert str(n) == "<M>(6, 5 => 0)"

def test_monster_3():
    m = MagicMock()
    m.width = MagicMock(return_value=38)
    m.height = MagicMock(return_value=30)
    n = Monster(6, 5, m, 1)
    assert n.speed == 1

def test_monster_4():
    m = MagicMock()
    m.width = MagicMock(return_value=38)
    m.height = MagicMock(return_value=30)
    n = Monster(6, 5, m, 5)
    assert n.speed < 6

def test_snake_1():
    g = MagicMock()
    s = Snake(g, Level(game_levels[0]['data']))
    assert s.level.to_pick == 254
    for i in range(0, 10):
        s.move_right()
    assert s.contains(25, 1)

def test_snake_2():
    g = MagicMock()
    s = Snake(g, Level(game_levels[0]['data']))
    assert s.spot_x == 19
    assert s.spot_y == 0

def test_snake_3():
    LEVEL = ["X@XX",
             "X .X",
             "X.$X"]
    l = Level(LEVEL)
    c = MagicMock()
    a = MagicMock()
    a.media_play_freeze = MagicMock()
    o = MagicMock()
    g = Game(c, a, o)
    g.to_pick = l.to_pick
    s = Snake(g, l)
    s.move_down()
    s.move_right()
    assert g.to_pick == 1
    assert g.score ==1
    assert g.is_frozen()

def test_snake_4():
    g = MagicMock()
    s = Snake(g, Level(game_levels[0]['data']))
    assert s.level.to_pick == 254
    for i in range(0, 10):
        s.move_right()
    for i in range(0, 10):
        s.move_left()
    assert not s.contains(25, 1)

def test_snake_5():
    g = MagicMock()
    s = Snake(g, Level(game_levels[0]['data']))
    s.blocks = []
    assert s.has_prev(7, 8) == False

def test_sword_1():
    m = MagicMock()
    m.width = MagicMock(return_value=5)
    m.height = MagicMock(return_value=5)
    s = Sword(2, 3, m)
    assert s.width == 5
    assert s.height == 5

def test_sword_2():
    m = MagicMock()
    m.width = MagicMock(return_value=5)
    m.height = MagicMock(return_value=5)
    s = Sword(2, 3, m)
    assert s.x == 2
    assert s.y == 3

def test_sword_3():
    m = MagicMock()
    m.width = MagicMock(return_value=5)
    m.height = MagicMock(return_value=5)
    s = Sword(2, 3, m)
    assert s.real_x == 60
    assert s.real_y == 190

def test_sword_4():
    m = MagicMock()
    m.width = MagicMock(return_value=5)
    m.height = MagicMock(return_value=5)
    s = Sword(2, 3, m)
    assert str(s) == "<S>(2, 3)"

def test_locale_1():
    assert Locale.get('ee', 'whatever') == None

def test_locale_2():
    assert Locale.get('pl', 'ctrl_line') is not None

def test_game_1():
    c = Configuration(CFG_FILE)
    n = MagicMock()
    a = MagicMock()
    with patch.object(Game, 'create_monsters', return_value=[]) as espresso:
        g = Game(n, a, c)
        g.game_initialize()
        assert g.lives == 3
        espresso.assert_called_once()

def test_game_2():
    c = Configuration(CFG_FILE)
    n = MagicMock()
    a = MagicMock()
    a.media_play_pick = MagicMock()
    with patch.object(Game, 'create_monsters', return_value=[]) as espresso:
        g = Game(n, a, c)
        g.game_initialize()
        g.snake.move_left()
        assert g.score == 1
        assert g.to_pick == 253
        a.media_play_pick.assert_called_once()
        espresso.assert_called_once()

def test_game_3():
    c = Configuration(CFG_FILE)
    n = MagicMock()
    a = MagicMock()
    a.media_play_pick = MagicMock()
    with patch.object(Game, 'create_monsters', return_value=[]) as espresso:
        g = Game(n, a, c)
        g.game_initialize()
        for i in range(0, 5):
            g.snake.move_left()
        assert g.score == 5
        assert g.to_pick == 249
        a.media_play_pick.call_count = 5
        espresso.assert_called_once()

def test_game_4():
    c = Configuration(CFG_FILE)
    n = MagicMock()
    a = MagicMock()
    a.media_play_pick = MagicMock()
    with patch.object(Game, 'create_monsters', return_value=[]) as espresso:
        g = Game(n, a, c)
        g.game_initialize()
        for i in range(0, 15):
            g.snake.move_left()
        for i in range(0, 4):
            g.snake.move_down()
        assert g.score == 19
        assert g.to_pick == 235
        a.media_play_pick.call_count = 19
        espresso.assert_called_once()

def test_game_5():
    c = Configuration(CFG_FILE)
    n = MagicMock()
    a = MagicMock()
    a.media_play_pick = MagicMock()
    a.media_play_diamond = MagicMock()
    with patch.object(Game, 'create_monsters', return_value=[]) as espresso:
        g = Game(n, a, c)
        g.game_initialize()
        for i in range(0, 15):
            g.snake.move_left()
        for i in range(0, 4):
            g.snake.move_down()
        for i in range(0, 2):
            g.snake.move_left()
        g.snake.move_up()
        assert g.score == 21
        assert g.to_pick == 233
        a.media_play_pick.call_count = 21
        a.media_play_diamond.called_count = 0
        espresso.assert_called_once()

def test_game_6():
    c = Configuration(CFG_FILE)
    n = MagicMock()
    a = MagicMock()
    a.media_play_pick = MagicMock()
    a.media_play_diamond = MagicMock()
    with patch.object(Game, 'create_monsters', return_value=[]) as espresso:
        with patch.object(Game, 'start_game', return_value=None) as latte:
            with patch.object(Game, 'paint', return_value=None) as americano:
                g = Game(n, a, c)
                g.game_initialize()
                g.next_level()
                assert g.counter == 999
                americano.assert_called_once()
            latte.assert_called_once()
        espresso.call_count == 2

def test_game_7():
    c = Configuration(CFG_FILE)
    n = MagicMock()
    a = MagicMock()
    a.media_play_pick = MagicMock()
    a.media_play_diamond = MagicMock()
    with patch.object(Game, 'create_monsters', return_value=[]) as espresso:
        with patch.object(Game, 'start_game', return_value=None) as latte:
            with patch.object(Game, 'paint', return_value=None) as americano:
                g = Game(n, a, c)
                g.game_initialize()
                g.configuration.set_mode(GameMode.EASY)
                g.next_level()
                assert g.counter == 240
                americano.assert_called_once()
            latte.assert_called_once()
        espresso.call_count == 2

def test_game_8():
    c = Configuration(CFG_FILE)
    n = MagicMock()
    a = MagicMock()
    a.media_play_pick = MagicMock()
    a.media_play_diamond = MagicMock()
    with patch.object(Game, 'create_monsters', return_value=[]) as espresso:
        with patch.object(Game, 'start_game', return_value=None) as latte:
            with patch.object(Game, 'paint', return_value=None) as americano:
                g = Game(n, a, c)
                g.game_initialize()
                g.configuration.set_mode(GameMode.EASY)
                for i in range(0, 9):
                    g.next_level()
                assert g.counter == 360
                assert g.board == GameBoard.GAMEOVER
                americano.call_count == 6
            latte.call_count == 3
        espresso.call_count == 2

def test_game_9():
    c = Configuration(CFG_FILE)
    n = MagicMock()
    a = MagicMock()
    a.media_play_pick = MagicMock()
    a.media_play_diamond = MagicMock()
    with patch.object(Game, 'create_monsters', return_value=[]) as espresso:
        with patch.object(Game, 'start_game', return_value=None) as latte:
            with patch.object(Game, 'paint', return_value=None) as americano:
                g = Game(n, a, c)
                g.change_state(GameState.PAUSED)
                americano.call_count == 6
            latte.call_count == 3
        espresso.call_count == 2

def test_game_10():
    c = Configuration(CFG_FILE)
    n = MagicMock()
    a = MagicMock()
    a.media_play_pick = MagicMock()
    a.media_play_diamond = MagicMock()
    with patch.object(Game, 'create_monsters', return_value=[]) as espresso:
        with patch.object(Game, 'start_game', return_value=None) as latte:
            with patch.object(Game, 'paint', return_value=None) as americano:
                g = Game(n, a, c)
                g.change_state(GameState.GAMEOVER)
                americano.call_count == 6
            latte.call_count == 3
        espresso.call_count == 2

def test_game_11():
    c = Configuration(CFG_FILE)
    n = MagicMock()
    a = MagicMock()
    a.media_play_pick = MagicMock()
    a.media_play_diamond = MagicMock()
    with patch.object(Game, 'create_monsters', return_value=[]) as espresso:
        with patch.object(Game, 'start_game', return_value=None) as latte:
            with patch.object(Game, 'paint', return_value=None) as americano:
                g = Game(n, a, c)
                g.change_state(GameState.INITIALIZED)
                americano.call_count == 6
            latte.call_count == 3
        espresso.call_count == 2

def test_game_12():
    c = Configuration(CFG_FILE)
    n = MagicMock()
    a = MagicMock()
    a.media_play_pick = MagicMock()
    a.media_play_diamond = MagicMock()
    with patch.object(Game, 'create_monsters', return_value=[]) as espresso:
        with patch.object(Game, 'start_game', return_value=None) as latte:
            with patch.object(Game, 'paint', return_value=None) as americano:
                g = Game(n, a, c)
                g.change_state(GameState.STARTED)
                americano.call_count == 6
            latte.call_count == 3
        espresso.call_count == 2

def test_game_13():
    c = Configuration(CFG_FILE)
    n = MagicMock()
    a = MagicMock()
    a.media_play_pick = MagicMock()
    a.media_play_diamond = MagicMock()
    with patch.object(Game, 'create_monsters', return_value=[]) as espresso:
        with patch.object(Game, 'start_game', return_value=None) as latte:
            with patch.object(Game, 'paint', return_value=None) as americano:
                g = Game(n, a, c)
                g.change_state(GameState.STARTED)
                americano.call_count == 6
            latte.call_count == 3
        espresso.call_count == 2

def test_get_orientation_1():
    p = SnakeBlock(5, 1, Move.BOTTOM)
    c = SnakeBlock(5, 2, Move.BOTTOM)
    n = SnakeBlock(6, 2, Move.RIGHT)
    assert get_orientation(p, c, n) == Orientation.NE

def test_get_orientation_2():
    p = SnakeBlock(5, 1, Move.BOTTOM)
    c = SnakeBlock(5, 2, Move.BOTTOM)
    n = SnakeBlock(4, 2, Move.LEFT)
    assert get_orientation(p, c, n) == Orientation.NW

def test_get_orientation_3():
    p = SnakeBlock(5, 5, Move.TOP)
    c = SnakeBlock(5, 4, Move.TOP)
    n = SnakeBlock(4, 4, Move.RIGHT)
    assert get_orientation(p, c, n) == Orientation.SE

def test_get_orientation_4():
    p = SnakeBlock(5, 5, Move.TOP)
    c = SnakeBlock(5, 4, Move.TOP)
    n = SnakeBlock(4, 4, Move.LEFT)
    assert get_orientation(p, c, n) == Orientation.SW

def test_get_orientation_5():
    p = SnakeBlock(5, 5, Move.TOP)
    c = SnakeBlock(5, 4, Move.TOP)
    n = SnakeBlock(5, 3, Move.TOP)
    assert get_orientation(p, c, n) == Orientation.VERTICAL

def test_get_orientation_6():
    p = SnakeBlock(5, 5, Move.LEFT)
    c = SnakeBlock(4, 5, Move.LEFT)
    n = SnakeBlock(3, 5, Move.LEFT)
    assert get_orientation(p, c, n) == Orientation.HORIZONTAL

def test_get_orientation_7():
    p = SnakeBlock(5, 5, Move.BOTTOM)
    c = SnakeBlock(5, 6, Move.BOTTOM)
    n = SnakeBlock(5, 7, Move.BOTTOM)
    assert get_orientation(p, c, n) == Orientation.VERTICAL

def test_get_orientation_8():
    p = SnakeBlock(5, 5, Move.RIGHT)
    c = SnakeBlock(6, 5, Move.RIGHT)
    n = SnakeBlock(7, 5, Move.RIGHT)
    assert get_orientation(p, c, n) == Orientation.HORIZONTAL
