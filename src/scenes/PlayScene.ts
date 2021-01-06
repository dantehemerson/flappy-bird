import { appConfig } from '../app.config'
import { Bird } from '../sprites/Bird'
import Phaser from 'phaser'

export class PlayScene extends Phaser.Scene {
	player: Phaser.Physics.Arcade.Sprite;
	cursors: any;
	private floor: Phaser.GameObjects.TileSprite
	private playing: boolean = false;


	constructor() {
    super({
			key: 'PlayScene'
			
		});
	}
	
	preload() {
		this.load.image('floor', '/assets/sprites/base.png')
		this.load.image('background', '/assets/sprites/background-day.png');
		this.load.image('player', '/assets/sprites/redbird-downflap.png');		
		this.load.image('player1', '/assets/sprites/redbird-midflap.png');		
		this.load.image('player2', '/assets/sprites/redbird-upflap.png');		
	}

	create() {
		this.add.image(0, 0, 'background').setOrigin(0, 0)

		this.floor = this.add.tileSprite(0, 452, appConfig.width, 100, 'floor')
		this.floor.setDepth(3);
		this.physics.add.existing(this.floor, false);
		this.floor.body.allowGravity = false;
		this.floor.body.setCollideWorldBounds(true);

		this.anims.create({
      key: 'fly',
        frames: [
            { key: 'player' },
            { key: 'player1' },
            { key: 'player2' },
        ],
        frameRate: 8,
        repeat: -1
    })

		this.player = this.physics.add.sprite(75, 100, 'bird').play('fly')
		this.player.body.allowGravity = true;
		this.player.body.height = 24;

		// this.player.body.setCollideWorldBounds(true);
		this.physics.add.collider(this.floor, this.player, null, null, this);


		this.input.on('pointerdown', this.jump, this)
	}



	update(time: number, delta:number) {
		if(!this.playing) this.player.setY(230)
		// console.log(" pOSITION Y", this.player.getTopRight())
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
		this.playIfNotPlaying()
		// this.player.setRotation(30)
	}

	playIfNotPlaying() {
		if(!this.playing) {
			this.player.setGravityY(1000)
			this.playing = true;
		}
	}
}
