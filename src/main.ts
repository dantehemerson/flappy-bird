import 'phaser';

import { PlayScene } from './scenes/PlayScene';

const config:GameConfig = {
    type: Phaser.AUTO,
    parent: 'content',
    width: 288,
    height: 512,
    resolution: 1,
    physics: {
      default: 'arcade',
      arcade: {
          gravity: { y: 600 },
          debug: false
      }
  },
    backgroundColor: "#EDEEC9",
    scene: [
      PlayScene
    ]
};

new Phaser.Game(config);
