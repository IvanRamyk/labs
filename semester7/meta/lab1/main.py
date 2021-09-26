import configparser

from game import Game


def main():
    config = configparser.ConfigParser()
    config.read("config.ini")
    game = Game(
        width=int(config["Screen"]["width"]),
        height=int(config["Screen"]["height"]),
        rows=int(config["Game"]["rows"]),
        columns=int(config["Game"]["columns"]),
        bubble_types=int(config["Game"]["bubble_types"]),
        frame_rate=int(config["Animation"]["frame_rate"]),
        caption="Bubble shooter"
    )
    game.run()


if __name__ == "__main__":
    main()
