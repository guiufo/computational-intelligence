using StatsBase

function evaluate(m)
	for i in 1:100
		send = more = money = 0
		send = m[i,1]*1000+m[i,2]*100+m[i,3]*10+m[i,4]
		more = m[i,5]*1000+m[i,6]*100+m[i,7]*10+m[i,2]
		money = m[i,5]*10000+m[i,6]*1000+m[i,3]*100+m[i,2]*10+m[i,8]
		m[i,end] = abs(send + more - money)
	end
	return m
end

function evaluateChildren(m)
	for i in 101:180
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
		m[i,1:end-1] = sample(0:9, 10, replace=false);
	end
	m[101:180,end] = 100000
	return m
end

function swapRows!(m, i, j)
    for k = 1:size(m,2)
        m[i,k], m[j,k] = m[j,k], m[i,k]
    end
end

function tournament(m)
	for i in 101:180
		best = 100000
		bestIndex = 1 
		# Make one tournament based on tour
		for j in 1:3
			randInt = rand(1:100)
			if m[randInt,end] < best
				best = m[randInt,end]
				bestIndex = randInt
			end	
		end	
		# Copy winner to i'th row of population
		m[i,:] = m[bestIndex,:]
	end
	return m
end

function swap!(x,y)
	temp = x
	x = y
	y = temp
end

function cyclicCrossover(m)
	for i in 101:179
		randIndex = rand(1:10)
		tempIndex = randIndex
		initialValue = m[i,randIndex]

		while m[i+1,tempIndex] != initialValue
			nextValue = m[i+1,tempIndex]
			swap!(m[i+1,tempIndex], m[i,tempIndex])
			for j in 1:10
				if j != tempIndex && m[i,j] == nextValue
					tempIndex = j
					break
				end
			end
		end
	end

	return m
end

#=
function cyclicCrossover(m)
	indexes = zeros(1,10)

	for i in 101:179
		randIndex = rand(1:10)
		indexes[randIndex] = 1
		initialValue = m[i,randIndex]

		while m[i+1,randIndex] != initialValue
			nextValue = m[i+1,randIndex]
			for j in 1:10 
				if m[i,j] == nextValue
					randIndex = j
					indexes[randIndex] = 1
				end	
			end	
		end	

		for j in 1:10
			if indexes[j] == 0
				temp = m[i,j]
				m[i,j] = m[i+1,j]
				m[i+1,j] = temp
			end
		end	
	end	

	return m
end
=#

	m = zeros(Int32,180,11)
	m = randomPopulation(m)
	m = evaluate(m)
	m = tournament(m)
	m = cyclicCrossover(m)
	m = evaluate(m)
	m = sortrows(m, by=x->x[end])
