class Snake {
    field Array bodyX; // x coordinates
    field Array bodyY; // y coordinates
    field int length;
    field int dirX;
    field int dirY;

    constructor Snake new() {
        let bodyX = Array.new(100);
        let bodyY = Array.new(100);
        let length = 3;
        let dirX = 1;  // moving right initially
        let dirY = 0;
        return this;
    }

    method void move() {
        var int i;
        let i = length;
        while (i > 0) {
            let bodyX[i] = bodyX[i-1];
            let bodyY[i] = bodyY[i-1];
            let i = i - 1;
        }
        let bodyX[0] = bodyX[0] + dirX;
        let bodyY[0] = bodyY[0] + dirY;

        // Check keyboard input
        if (Keyboard.keyPressed(Keyboard.UP)) { let dirX = 0; let dirY = -1; }
        if (Keyboard.keyPressed(Keyboard.DOWN)) { let dirX = 0; let dirY = 1; }
        if (Keyboard.keyPressed(Keyboard.LEFT)) { let dirX = -1; let dirY = 0; }
        if (Keyboard.keyPressed(Keyboard.RIGHT)) { let dirX = 1; let dirY = 0; }

        return;
    }

    method void grow() {
        let length = length + 1;
        return;
    }

    method int headX() { return bodyX[0]; }
    method int headY() { return bodyY[0]; }

    method boolean hitWall() {
        if (bodyX[0] < 0 | bodyX[0] > 79 | bodyY[0] < 0 | bodyY[0] > 49) {
            return true;
        }
        return false;
    }

    method boolean hitSelf() {
        var int i;
        let i = 1;
        while (i < length) {
            if (bodyX[0] = bodyX[i] & bodyY[0] = bodyY[i]) { return true; }
            let i = i + 1;
        }
        return false;
    }

    method void draw() {
        var int i;
        let i = 0;
        while (i < length) {
            do Screen.setPixel(bodyX[i], bodyY[i], true);
            let i = i + 1;
        }
        return;
    }
}
