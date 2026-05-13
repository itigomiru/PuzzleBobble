$p = 'program/GlidManager.cpp'
$t = [System.IO.File]::ReadAllText($p)

$oldUpdate = @"
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			if (glid[row][col].state != EMPTY && glid[row][col].state != INVALID) {
				glid[row][col].blinkTimer++;
				// �u���̎�����ݒ� (��300�t���[�� = ��5�b��1��u��)
				if (glid[row][col].blinkTimer >= 300) {
					glid[row][col].blinkTimer = 0;
				}
			}
		}
	}
"@
$newUpdate = @"
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			if (glid[row][col].state != EMPTY && glid[row][col].state != INVALID) {
				if (!glid[row][col].wasLuminus) {
					glid[row][col].luminusTimer++;
					if (glid[row][col].luminusTimer >= 18) {
						glid[row][col].luminusTimer = 0;
						glid[row][col].wasLuminus = true;
					}
				} else {
					glid[row][col].blinkTimer++;
					if (glid[row][col].blinkTimer >= 300) {
						glid[row][col].blinkTimer = 0;
					}
				}
			}
		}
	}
"@

$oldRender = @"
				int srcX = 0;
				if (!glid[row][col].wasLuminus) {
					srcX = 16 * ((glid[row][col].luminusTimer / 3) % 3);
				}
				else if (glid[row][col].blinkTimer >= 290) {
					int frame = glid[row][col].blinkTimer - 290;
					if (frame < 3) srcX = 16 * 1; 
					else if (frame < 7) srcX = 16 * 2; 
					else srcX = 16 * 0; 
				}
"@
$newRender = @"
				int srcX = 0;
				if (!glid[row][col].wasLuminus) {
					srcX = 16 * ((glid[row][col].luminusTimer / 3) % 3);
				} else if (glid[row][col].blinkTimer >= 290) {
					int frame = glid[row][col].blinkTimer - 290;
					if (frame < 3) srcX = 16 * 1;
					else if (frame < 7) srcX = 16 * 2;
					else srcX = 16 * 0;
				}
"@

if (-not $t.Contains($oldUpdate)) { throw 'Update block not found' }
if (-not $t.Contains($oldRender)) { throw 'Render block not found' }
$t = $t.Replace($oldUpdate, $newUpdate)
$t = $t.Replace($oldRender, $newRender)
[System.IO.File]::WriteAllText($p, $t)
