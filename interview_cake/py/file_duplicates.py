import unittest
import os
import hashlib

# Determined that Mac OSX block size = 4096 bytes via
# $ diskutil info / | grep "Block Size"
def calculateMD5_fast(filename, block_size=2**12):
	"""Returns MD% checksum for given file (3 block sample)
	"""
	md5 = hashlib.md5()
	try:
		# get size of file in blocks
		size = os.path.getsize(filename) // block_size + 1
		print("blocks in file: %d" % size)

		# open the file for reading in binary format
		file = open(filename, 'rb')

		if size < 3:
			data = file.read()
			md5.update(data)
		else:
			# read and hash the first block
			data = file.read(block_size)
			md5.update(data)

			# hash the middle block
			file.seek((size // 2) * block_size)
			data = file.read(block_size)
			md5.update(data)

			# hash the last block
			file.seek((size - 1) * block_size)
			data = file.read(block_size)
			md5.update(data)

	except IOError:
		print('File \'' + filename + '\' not found!')
		return None
	except:
		return None
	return md5.hexdigest()

# dictionary to store files
found = {}

# list to store duplicates when found
duplicates = []

# Set the directory you want to start from
rootDir = '../data'
for dirName, subdirList, fileList in os.walk(rootDir):
	print('Found directory: %s' % dirName)
	for fname in fileList:
		print('\t%s' % fname)
		current_file = dirName + '/' + fname
		key = calculateMD5_fast(current_file)
		if key not in found:
			found[key] = current_file
		else:
			# the duplicate file must come first in our tuple
			# we assume the most recently modified file is the duplicate
			if os.stat(found[key]).st_mtime > os.stat(current_file).st_mtime:
				item = found[key], current_file
			else:
				item = current_file, found[key]
			duplicates.append(item)
print(found)
print(duplicates)
