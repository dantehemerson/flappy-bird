import Phaser from 'phaser'
import { PlayScene } from './scenes/PlayScene';

const config: Phaser.Types.Core.GameConfig = {
    type: Phaser.AUTO,
    parent: 'content',
    width: 288 ,
    height: 502,
    // resolution: 1.4,
    physics: {
      default: 'arcade',
      arcade: {
          gravity: { y: 600 },
          debug: false,
      }
  },
    backgroundColor: "#EDEEC9",
    scene: [
      PlayScene
    ]
};
new Phaser.Game(config);
