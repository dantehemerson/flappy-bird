import Phaser from 'phaser'

export class Bird extends Phaser.Physics.Arcade.Sprite {
  private alive: boolean
  private bird

  constructor(scene, x, y) {
    super(scene, x, y, 'brain')

    this.body.allowGravity = true;
    
    


  }

  
  fly() {

  }

  update() {
    this.play('fly',true)
  }

}