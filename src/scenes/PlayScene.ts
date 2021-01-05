import { appConfig } from '../app.config'

export class PlayScene extends Phaser.Scene {
	player: Phaser.Physics.Arcade.Sprite;
	cursors: any;
	private floor: Phaser.GameObjects.TileSprite

	constructor() {
    super({
			key: 'PlayScene'
		});
	}
	
	preload() {
		this.load.image('floor', '/assets/sprites/base.png')
		this.load.image('background', '/assets/sprites/background-day.png');
		this.load.image('player', '/assets/sprites/redbird-midflap.png');		
	}

	create() {
		this.add.image(0, 0, 'background').setOrigin(0, 0)

		this.floor = this.add.tileSprite(0, 462, appConfig.width, 100, 'floor')
		this.floor.setDepth(3);
		this.physics.add.existing(this.floor, false);
		this.floor.body.allowGravity = false;
		this.floor.body.setCollideWorldBounds(true);

		this.player  = this.physics.add.sprite(100, 200, 'player')
		this.player.setGravityY(1000)

		this.input.on('pointerdown', this.jump, this)
	}



	update(time: number, delta:number) {
		this.floor.tilePositionX += 2.5
		this.limits()
		
	}
	

	limits() {
		const vector = this.player.getCenter() as any
		if(vector.y < -200) {
			this.player.setY(-200)
		} else if(vector.y > appConfig.height) {
			this.player.setY(appConfig.height)
		}
	}

	jump() {
		this.player.setVelocityY(-350)
		this.player.setRotation(30)
		console.log('Pressing key', this.player.getTopLeft())
	}
}
