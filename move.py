import sys
import asyncio
from pyartnet import ArtNetNode

async def main():
	node = ArtNetNode('192.168.0.200', 6454)
	universe = node.add_universe(0)

	X = (int(sys.argv[1]) * 5) + 1
	# Y = (int(sys.argv[2])-1)*19

	channel = universe.add_channel(start=1, width=4)

	channel.add_fade([X, 1, 0, 5], 1)

	await channel


asyncio.run(main())
