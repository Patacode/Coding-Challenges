# frozen_string_literal: true

require 'bloom_filter'

RSpec.configure do |config|
  config.before(:context, target_cls: BloomFilter) do
    @bloom_filter = BloomFilter.new('dict_sample.txt', epsilon: 0.1)
  end

  config.before(:example, fresh_data: true) do
    @bloom_filter = BloomFilter.new('dict_sample.txt', epsilon: 0.1)
  end
end

RSpec.describe BloomFilter, target_cls: BloomFilter do
  describe '#size' do
    it 'returns the number of bits used by the bloom filter' do
      expect(@bloom_filter.size).to eq(480)
    end
  end

  describe '#hash_function_count' do
    it 'returns the number of hash functions used by the bloom filter' do
      expect(@bloom_filter.hash_function_count).to eq(4)
    end
  end

  describe '#to_i' do
    it 'returns the bit array value as integer used by the bloom filter' do
      expect(@bloom_filter.to_i).to eq(
        '12700271158760067064329340718225424671980043543329009783377009459400' \
        '87273989570313276819506087179542471113271943694014107953142208471521' \
        '828171362'.to_i
      )
    end
  end

  describe '#add', fresh_data: true do
    it 'adds the provided element to the bloom filter' do
      @bloom_filter.add('hello')

      expect(@bloom_filter.to_i).to eq(
        '12700271158760067064329340718225424671980043543329009783377009459400' \
        '87273989570313276819506087179542471113271943694647933253256323172270' \
        '179774050'.to_i
      )
    end
  end

  describe '#include?', fresh_data: true do
    it 'returns true if the provided element is most likely in the set' do
      expect(@bloom_filter.include?('deleniti')).to be(true)
    end

    it 'returns false if the provided element is most likely not in the set' do
      expect(@bloom_filter.include?('zebra')).to be(false)
    end
  end

  describe '#save_to_file' do
    after(:example) do
      FileUtils.rm_f('result.bf')
    end

    it 'saves the internal bit array of bloom filter in a file on disk' do
      @bloom_filter.save_to_file('result')

      expect(File).to exist('result.bf')
      expect(File.read('result.bf')).to eq(
        "h&#\xDA\xAA\x88.:r&\xB6\xBA\xE6\xEE!+6\xA6\x1Cf\tdjv\xB3\xAE:#\xB2" \
        "\xA3:\xA3fc\xA6c,\xC0\xA6'(\xE2\xBF&\xB3\xAA\xE3\xA66\xE7\xB6&N(\xAA" \
        "\xF5\xB2rnb"
      )
    end
  end
end
