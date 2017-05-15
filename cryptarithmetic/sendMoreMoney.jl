#=
Program to solve the "send + more = money" problem
Each individual is a row in a 180 x 11 matrix
Positions 1 to 10 is for the permutation
The individual is the positions from 1 to 8
The order of the row is "sendmoryXY"
XY holds digits to facilitate crossover and mutation
=#
using StatsBase
include("MyModule.jl")

"Evaluate all individuals"
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

"Generate 100 individuals with size 10"
function randomPopulation(m)
	for i in 1:100
		m[i,1:end-1] = sample(0:9, 10, replace=false)
	end
	return m
end

"Make a roulette and select 80 individuals"
function roulette(m)
	fitnessSum = sum(m[1:100,end])
	pSum = 0.0
	rouletteValues = zeros(Float64,100)
	# mount the roulette
	for i in 1:100
		rouletteValues[i] = pSum + (m[i,end]/fitnessSum)
		pSum += rouletteValues[i]
	end

	for i in 101:180
		spin = rand()*pSum
		selected = 1
		for j in 1:99
			if spin > rouletteValues[j] && spin <= rouletteValues[j+1]
				selected = j
				break
			end
		end
		m[i,:] = m[selected,:]
	end
	return m
end


"Makes a tournament with tour of 3"
function tournament(m)
	for i in 101:180
		best = 100000
		bestIndex = 1 
		for j in 1:3
			randInt = rand(1:100)
			if m[randInt,end] < best
				best = m[randInt,end]
				bestIndex = randInt
			end	
		end	
		m[i,:] = m[bestIndex,:]
	end
	return m
end

"Makes a cyclic crossover in selected fathers"
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

"Mutates 10% of the generated children"
function mutation(m)
	for i in 1:8
		randRow = rand(101:180)
		randColumn = rand(1:8)
		randXY = rand(9:10)
		m[randRow,randColumn],m[randRow,randXY] = m[randRow,randXY],m[randRow,randColumn] 
	end
	return m
end

"Usage: run(<number of experiments>, <generations per experiments>)"
function run(nexperiments, ngenerations)
	counter = 0
	for i in 1:nexperiments
		m = zeros(Int32,180,11)
		m = randomPopulation(m)
		m = evaluate(m)

		for j in 1:ngenerations
			m = tournament(m)
			#m = roulette(m)
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
	@printf("%s experiments and %s generations:\n", nexperiments, ngenerations)
	@printf("%2.1f%% of sucess\n", (counter/nexperiments)*100)
	return
end
