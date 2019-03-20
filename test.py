#!/usr/bin/env python3

import subprocess
import time


def main():
	start_time = time.time()

	result = subprocess.run(
		args=['./reverse_seed', 'map_information.txt'],
		stdout=subprocess.PIPE,
		check=True)
	print()

	print('time used: {:.3f}s'.format(time.time() - start_time))

	stdout = result.stdout.decode()
	try:
		assert 'Debug low 20 bit list:\n  1' in stdout
		assert 'Debug low 48 bit list:\n  1' in stdout
		assert 'Possible seeds:\n  1' in stdout
	except AssertionError:
		print('======= STDOUT =======')
		print(stdout)
		print('===== END STDOUT =====')
		raise
	else:
		print('Test passed')


if __name__ == '__main__':
	main()
