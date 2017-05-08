using StatsBase

function evaluate(m)
	for i in 1:180
		send = more = money = 0
		send = m[i,1]*1000+m[i,2]*100+m[i,3]*10+m[i,4]
		more = m[i,5]*1000+m[i,6]*100+m[i,7]*10+m[i,2]
		money = m[i,5]*10000+m[i,6]*1000+m[i,3]*100+m[i,2]*10+m[i,8]
		m[i,end] = abs(send + more - money)
	end
	return m
end

function randomPopulation(m)
	for i in 1:100
		m[i,1:end-1] = sample(0:9, 10, replace=false)
	end
	return m
end

function tournament(m)
	for i in 101:180
		best = 100000
		bestIndex = 1 
		# Make one tournament
		for j in 1:3
			randInt = rand(1:100)
			if m[randInt,end] < best
				best = m[randInt,end]
				bestIndex = randInt
			end	
		end	
		# Copy winner
		m[i,:] = m[bestIndex,:]
	end
	return m
end

function cyclicCrossover(m)
	for i in 101:179
		tempIndex = rand(1:10)
		initialValue = m[i,tempIndex]

		while m[i+1,tempIndex] != initialValue
			nextValue = m[i+1,tempIndex]
			
			m[i+1,tempIndex],m[i,tempIndex] = m[i,tempIndex],m[i+1,tempIndex]

			for j in 1:10
				if j != tempIndex && m[i,j] == nextValue
					tempIndex = j
					break
				end
			end
		end
		# Make the last swap, closing the cycle
		m[i+1,tempIndex],m[i,tempIndex] = m[i,tempIndex],m[i+1,tempIndex]

	end
	return m
end

function mutation(m)
	for i in 1:8
		randRow = rand(101:180)
		randColumn = rand(1:8)
		randXY = rand(9:10)
		m[randRow,randColumn],m[randRow,randXY] = m[randRow,randXY],m[randRow,randColumn] 
	end
	return m
end

global counter = 0

for i in 1:1000
	m = zeros(Int32,180,11)
	m = randomPopulation(m)
	m = evaluate(m)

	for j in 1:200
		m = tournament(m)
		m = cyclicCrossover(m)
		m = mutation(m)
		m = evaluate(m)
		m = sortrows(m, by=x->x[end])
		if m[1,end] == 0
			counter += 1
			break
		end
	end
end

println(counter/1000)
