import unittest
from engine import Engine
import xmlrunner

class EngineTest(unittest.TestCase):

    @classmethod
    def setUpClass(self):
        self.stone = []
        self.eng = Engine()

    def test01_get_stone_layout(self):
        self.stone = self.eng.get_stone_layout()
        length =len(self.stone)
        self.assertTrue(type(self.stone) is list)
        self.assertEqual(81,length)
        for a in self.stone:
            self.assertEqual('gray', a)

    def test02_clear_board(self):
        self.stone = self.eng.clear_board()
        self.assertTrue(type(self.stone) is list)
        self.assertEqual(81, len(self.stone))

    def test03_get_status(self):
        answer = self.eng.get_status()
        self.assertFalse(answer)

    def test04_start_game(self):
        self.stone = self.eng.start_game()
        length = len(self.stone)
        self.assertTrue(type(self.stone) is list)
        self.assertEqual(81, length)
        for a in self.stone:
            self.assertEqual('gray', a)

    def test05_status_after_start_game(self):
        answer = self.eng.get_status()
        self.assertTrue(answer)
    def test06_get_move(self):
        answer = self.eng.get_move()
        self.assertEqual('black',answer)


if __name__=='__main__':
    runner = xmlrunner.XMLTestRunner(output='test-reports')
    unittest.main(testRunner=runner)

    #unittest.main()